package main

import (
	"bytes"
	"encoding/binary"
	"errors"
)

type Monster struct {
	pos_x float32
	pos_y float32
	width int
	height int
	velocity int
	health uint8
	damage int
}

func NewMonster(pos_x float32, pos_y float32) *Monster {
	new_monster := Monster{}
	new_monster.pos_x = pos_x
	new_monster.pos_y = pos_y
	new_monster.width = 44
	new_monster.height = 31
	new_monster.velocity = 3
	new_monster.health = 3
	new_monster.damage = 1
	
	return &new_monster
}

func (monster *Monster)Format() (*bytes.Buffer, error) {
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

	return buf, nil
}
