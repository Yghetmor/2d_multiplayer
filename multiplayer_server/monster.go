package main

import (
	"bytes"
	"encoding/binary"
	"errors"
	"math"
)

type Monster struct {
	pos_x    float32
	pos_y    float32
	angleDeg float32
	health   int8
	isDead bool
}

func NewMonster(pos_x float32, pos_y float32) *Monster {
	return &Monster{
		pos_x:  pos_x,
		pos_y:  pos_y,
		health: int8(MONSTER_HEALTH),
	}
}

func (monster Monster) bufferFormat() (*bytes.Buffer, error) {
	buf := new(bytes.Buffer)
	err := buf.WriteByte(byte('-'))
	if err != nil {
		return nil, errors.New("binary write into buffer failed")
	}
	err = binary.Write(buf, binary.LittleEndian, uint16(monster.pos_x))
	if err != nil {
		return nil, errors.New("binary write into buffer failed")
	}
	err = binary.Write(buf, binary.LittleEndian, uint16(monster.pos_y))
	if err != nil {
		return nil, errors.New("binary write into buffer failed")
	}
	err = binary.Write(buf, binary.LittleEndian, monster.health)
	if err != nil {
		return nil, errors.New("binary write into buffer failed")
	}
	err = binary.Write(buf, binary.LittleEndian, uint16(monster.angleDeg))
	if err != nil {
		return nil, errors.New("binary write into buffer failed")
	}

	return buf, nil
}

func (monster *Monster) UpdatePosition(player Player) {
	player_x := player.pos_x
	player_y := player.pos_y
	var calc_angle float64

	if monster.pos_y == player_y {
		if monster.pos_x > player_x {
			calc_angle = 270.0
		} else {
			calc_angle = 90.0
		}
	} else {
		arctan := math.Atan((float64(player_x) - float64(monster.pos_x)) / (float64(monster.pos_y) - float64(player_y)))
		calc_angle = arctan * 180.0 / math.Pi

		if monster.pos_y < player_y {
			calc_angle += 180.0
		}
	}

	if calc_angle < 180.0 {
		monster.angleDeg = float32(calc_angle) + 180.0
	} else {
		monster.angleDeg = float32(calc_angle) - 180.0
	}

	vel_x := float64(MONSTER_VELOCITY) * math.Sin(calc_angle*math.Pi/180.0)
	vel_y := (-1.0) * float64(MONSTER_VELOCITY) * math.Cos(calc_angle*math.Pi/180.0)

	monster.pos_x += float32(vel_x)
	monster.pos_y += float32(vel_y)

	if monster.pos_x < 50 {
		monster.pos_x = 50
	} else if monster.pos_x > float32(MAP_WIDTH)-50-float32(MONSTER_WIDTH) {
		monster.pos_x = float32(MAP_WIDTH) - 50 - float32(MONSTER_WIDTH)
	}

	if monster.pos_y < 50 {
		monster.pos_y = 50
	} else if monster.pos_y > float32(MAP_HEIGHT)-50-float32(MONSTER_HEIGHT) {
		monster.pos_y = float32(MAP_HEIGHT) - 50 - float32(MONSTER_HEIGHT)
	}
}
