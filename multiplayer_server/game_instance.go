package main

import (
	"bytes"
	"encoding/binary"
	"io"
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
	// monster_start_time := time.Now()

	monsters = append(monsters, NewMonster(float32(MAP_WIDTH) - 100, float32(MAP_HEIGHT) - 100))

	for {
		elapsed_time := time.Since(start_time).Milliseconds()
		// monster_spawn_time := time.Since(monster_start_time).Seconds() 

		if elapsed_time > 1000 / int64(FPS) {

			player_new_pos_buf := make([]byte, 1024)
			n, err := player.connection.Read(player_new_pos_buf)
			if err == io.EOF {
				log.Println("Client closed the connection")
				player_conn.Close()
				return
			} else if err != nil {
				log.Println("Couldn't receive from player connection : ", err)
			}

			if n == 5 {
				player.UpdatePosition(player_new_pos_buf)
			} else {
				log.Println("Couldn't update player position : did not receive 5 bytes")
			}

			var output_infos []byte

			for _, monster := range monsters {
				(*monster).UpdatePosition(player)
				formatted, err := (*monster).Format()
				if err != nil {
					log.Println("Error while formatting monster : ", err)
					continue
				}

				log.Println("Monster coords - x : ", monster.pos_x, " - y : ", monster.pos_y)

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

		// if monster_spawn_time > 3 {
		// 	player_x := player.pos_x
		// 	player_y := player.pos_y
		//
		// 	if player_x < float32(MAP_WIDTH) / 2 && player_y < float32(MAP_HEIGHT) / 2 {
		// 		monsters = append(monsters, NewMonster(float32(MAP_WIDTH) - 100, float32(MAP_HEIGHT) - 100))
		// 	} else if player_x > float32(MAP_WIDTH) / 2 && player_y < float32(MAP_HEIGHT) / 2 {
		// 		monsters = append(monsters, NewMonster(100, float32(MAP_HEIGHT) - 100))
		// 	} else if player_x < float32(MAP_WIDTH) / 2 && player_y > float32(MAP_HEIGHT) / 2 {
		// 		monsters = append(monsters, NewMonster(float32(MAP_WIDTH) - 100, 100))
		// 	} else {
		// 		monsters = append(monsters, NewMonster(100, 100))
		// 	}
		//
		// 	monster_start_time = time.Now()
		// }
	}
}
