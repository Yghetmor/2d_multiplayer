package main

import (
	"bytes"
	"encoding/binary"
	"errors"
	"net"
)

type Player struct {
	id         uint8
	connection net.Conn
	pos_x      float32
	pos_y      float32
	angleDeg      float32
	health     uint8
	click	   bool
}

func NewPlayer(id uint8, connection net.Conn) Player {
	return Player{
		id:         id,
		connection: connection,
		pos_x:      float32(MAP_WIDTH / 2),
		pos_y:      float32(MAP_HEIGHT / 2),
		health:     uint8(PLAYER_HEALTH),
	}
}

func (player Player) bufferFormat() (*bytes.Buffer, error) {
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
	err = binary.Write(buf, binary.LittleEndian, uint16(player.angleDeg))
	if err != nil {
		return nil, errors.New("binary write into buffer failed")
	}

	return buf, nil
}

func (player *Player) UpdatePosition(buf_in []byte) error {
	reader := bytes.NewReader(buf_in)

	var data struct {
		Pos_x uint16
		Pos_y uint16
		Angle uint16
		Click uint8
	}

	if err := binary.Read(reader, binary.LittleEndian, &data); err != nil {
		return errors.New("binary.Read failed")
	}

	player.pos_x = float32(data.Pos_x)
	player.pos_y = float32(data.Pos_y)
	player.angleDeg = float32(data.Angle)
	if data.Click == 0 {
		player.click = false
	} else {
		player.click = true
	}

	return nil
}
