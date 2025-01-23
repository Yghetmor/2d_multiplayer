package main

import (
	"bytes"
	"encoding/binary"
	"errors"
)

type Player struct {
	id uint8
	pos_x float32
	pos_y float32
	angle float32
	health uint8
}

func NewPlayer(id uint8, pos_x float32, pos_y float32, angle float32) *Player {
	new_player := Player{}
	new_player.id = id
	new_player.pos_x = pos_x
	new_player.pos_y = pos_y
	new_player.angle = angle
	new_player.health = uint8(PLAYER_HEALTH)

	return &new_player
}

func (player *Player)Format() (*bytes.Buffer, error) {
	buf := new(bytes.Buffer)
	err := buf.WriteByte(byte('*'))
	if err != nil {
		return nil, errors.New("binary write into buffer failed")
	}
	err = binary.Write(buf, binary.LittleEndian, player.id)
	if err != nil {
		return nil, errors.New("binary write into buffer failed")
	}
	err = binary.Write(buf, binary.LittleEndian, uint16(player.pos_x))
	if err != nil {
		return nil, errors.New("binary write into buffer failed")
	}
	err = binary.Write(buf, binary.LittleEndian, uint16(player.pos_y))
	if err != nil {
		return nil, errors.New("binary write into buffer failed")
	}
	err = binary.Write(buf, binary.LittleEndian, player.health)
	if err != nil {
		return nil, errors.New("binary write into buffer failed")
	}
	err = binary.Write(buf, binary.LittleEndian, player.angle)
	if err != nil {
		return nil, errors.New("binary write into buffer failed")
	}

	return buf, nil
}
