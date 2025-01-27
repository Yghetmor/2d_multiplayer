package main

import (
	"bytes"
	"encoding/binary"
	"errors"
	"math"
)

type Projectile struct {
	pos_x float32
	pos_y float32
	vel_x float32
	vel_y float32
	angle float32 // angle in degrees
	alive bool
}

func NewProjectile(pos_x float32, pos_y float32, angle float32) *Projectile {
	new_projectile := Projectile{}
	new_projectile.pos_x = pos_x
	new_projectile.pos_y = pos_y
	new_projectile.angle = angle

	var calc_angle float32 = 0.0
	if angle < 180.0 {
		calc_angle = angle + 180.0
	} else {
		calc_angle = angle - 180.0
	}

	new_projectile.vel_x = float32(PROJECTILE_VELOCITY) * float32(math.Sin(float64(calc_angle) * math.Pi / 180.0))
	new_projectile.vel_y = (-1) * float32(PROJECTILE_VELOCITY) * float32(math.Cos(float64(calc_angle) * math.Pi / 180.0))

	new_projectile.alive = true

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
	err = binary.Write(buf, binary.LittleEndian, uint8(projectile.angle))
	if err != nil {
		return nil, errors.New("binary write into buffer failed")
	}

	return buf, nil
}

func (projectile *Projectile)UpdatePosition() {
	projectile.pos_x += projectile.vel_x
	projectile.pos_y += projectile.vel_y

	if projectile.pos_x < 50 || projectile.pos_x > float32(MAP_WIDTH) - 50 - float32(PROJECTILE_WIDTH) || projectile.pos_y < 50 || projectile.pos_y > float32(MAP_HEIGHT) - 50 - float32(PROJECTILE_HEIGHT) {
		projectile.alive = false
	}
}
