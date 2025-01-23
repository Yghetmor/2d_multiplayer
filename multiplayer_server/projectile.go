package main

import (
	"bytes"
	"encoding/binary"
	"errors"
)

type Projectile struct {
	pos_x float32
	pos_y float32
	angle float32 // angle in degrees
	width int
	height int
	velocity int
	damage int
}

func NewProjectile(pos_x float32, pos_y float32, angle float32) *Projectile {
	new_projectile := Projectile{}
	new_projectile.pos_x = pos_x
	new_projectile.pos_y = pos_y
	new_projectile.angle = angle
	new_projectile.width = 6
	new_projectile.height = 16 
	new_projectile.velocity = 10
	new_projectile.damage = 1

	return &new_projectile
}

func (projectile *Projectile)Format() (*bytes.Buffer, error) {
	buf := new(bytes.Buffer)
	err := buf.WriteByte(byte('*'))
	if err != nil {
		return nil, errors.New("binary write into buffer failed")
	}
	err = binary.Write(buf, binary.LittleEndian, float32(projectile.pos_x))
	if err != nil {
		return nil, errors.New("binary write into buffer failed")
	}
	err = binary.Write(buf, binary.LittleEndian, float32(projectile.pos_y))
	if err != nil {
		return nil, errors.New("binary write into buffer failed")
	}
	err = binary.Write(buf, binary.LittleEndian, projectile.angle)
	if err != nil {
		return nil, errors.New("binary write into buffer failed")
	}

	return buf, nil
}

