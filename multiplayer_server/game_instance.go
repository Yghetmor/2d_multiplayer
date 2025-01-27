package main

import (
	"bytes"
	"encoding/binary"
	"log"
	"net"
	"slices"
	"time"
)

func StartInstance(conn_in_channel chan net.Conn, player_conn net.Conn) {
	player := NewPlayer(1, player_conn)
	monsters := []*Monster{}
	projectiles := []*Projectile{}

	start_time := time.Now()

	for {
		elapsed_time := time.Since(start_time).Milliseconds()
		if elapsed_time > 1000 / int64(FPS) {
			player_new_pos_buf := make([]byte, 1024)
			n, err := player.connection.Read(player_new_pos_buf)
			if err != nil {
				log.Println("Couldn't receive from player connection : ", err)
			}
			if n > 8 {
				player.UpdatePosition(player_new_pos_buf)
			}

			var output_infos []byte

			for _, monster := range monsters {
				(*monster).UpdatePosition(player)
				formatted, err := (*monster).Format()
				if err != nil {
					log.Println("Error while formatting monster : ", err)
					continue
				}
				output_infos = slices.Concat(output_infos, formatted.Bytes())
			}
			for _, projectile := range projectiles {
				(*projectile).UpdatePosition()
				formatted, err := (*projectile).Format()
				if err != nil {
					log.Println("Error while formatting projectile : ", err)
					continue
				}
				output_infos = slices.Concat(output_infos, formatted.Bytes())
			}

			output_with_len := new(bytes.Buffer)
			err = binary.Write(output_with_len, binary.LittleEndian, uint16(len(output_infos)))
			output_with_len.Write(output_infos)

			_, err = player.connection.Write(output_with_len.Bytes())
			if err != nil {
				log.Println("Error while sending data to client : ", err)
			}

			start_time = time.Now()
		}
	}
}
