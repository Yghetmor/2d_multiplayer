package main

import (
	"bytes"
	"testing"
)

func TestFormat(t *testing.T) {
	var monster_x float32 = 0x0040
	var monster_y float32 = 0x0040
	test_monster := NewMonster(monster_x, monster_y)
	test_buffer, err := test_monster.bufferFormat()
	if err != nil {
		t.Fatal("Format() function failed!")
	}

	expected_buffer := [7]byte{byte('-'), 0x40, 0x00, 0x40, 0x00, 0x03, 0x00}
	if !bytes.Equal(test_buffer.Bytes(), expected_buffer[:]) {
		t.Fatal("bufferFormat() function returns wrong answer! expexted : ", expected_buffer[:], " Got : ", test_buffer.Bytes())
	}
}
