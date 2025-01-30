package main

import (
	"testing"
)

func TestPlayerUpdatePosition(t *testing.T) {
	player := NewPlayer(1, nil)
	var new_pos_x uint16 = 0x0040
	var new_pos_y uint16 = 0x0060
	var new_angle float32 = 140.0

	test_input := [5]byte{0x40, 0x00, 0x60, 0x00, 0x8C}
	player.UpdatePosition(test_input[:])

	if player.pos_x != float32(new_pos_x) {
		t.Fatal("UpdatePosion() returns wrong pos_x")
	}
	if player.pos_y != float32(new_pos_y) {
		t.Fatal("UpdatePosion() returns wrong pos_y")
	}
	if player.angle != new_angle {
		t.Fatal("UpdatePosion() returns wrong angle")
	}
}
