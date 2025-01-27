package main

import (
	"bytes"
	"encoding/binary"
	"errors"
	"net"
)

type Player struct {
	id uint8
	connection net.Conn
	pos_x float32
	pos_y float32
	angle float32
	health uint8
}

func NewPlayer(id uint8, connection net.Conn) *Player {
	new_player := Player{}
	new_player.id = id
	new_player.connection = connection
	new_player.pos_x = float32(MAP_WIDTH / 2)
	new_player.pos_y = float32(MAP_HEIGHT / 2)
	new_player.angle = 0
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
	err = binary.Write(buf, binary.LittleEndian, uint8(player.angle))
	if err != nil {
		return nil, errors.New("binary write into buffer failed")
	}

	return buf, nil
}

func (player *Player)UpdatePosition(buf_in []byte) error {
	reader := bytes.NewReader(buf_in)

	var data struct {
		Pos_x uint16
		Pos_y uint16
		Angle uint8
	}

	if err := binary.Read(reader, binary.LittleEndian, &data); err != nil {
		return errors.New("binary.Read failed")
	}

	player.pos_x = float32(data.Pos_x)
	player.pos_y = float32(data.Pos_y)
	player.angle = float32(data.Angle)

	return nil
}
