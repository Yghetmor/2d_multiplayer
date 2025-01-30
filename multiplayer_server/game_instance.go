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

	// var udp_port uint16 = 60000
	// udp_port_bytes := new(bytes.Buffer)
	// err := binary.Write(udp_port_bytes, binary.LittleEndian, udp_port)
	// if err != nil {
	// 	log.Println("Error in binary write of udp port : ", err)
	// 	return
	// }
	//
	// _, err = player.connection.Write(udp_port_bytes.Bytes())
	// if err != nil {
	// 	log.Println("Error in sending udp port : ", err)
	// 	return
	// }

	udpClientAddr, err := net.ResolveUDPAddr("udp", "localhost:40000")
	if err != nil {
		log.Println("Couldn't resolve UDP address : ", err)
		return
	}

	udpConn, err := net.ListenUDP("udp", udpClientAddr)
	if err != nil {
		log.Println("Couldn't listen to UDP : ", err)
		return
	}
	defer udpConn.Close()

	start_time := time.Now()
	// monster_start_time := time.Now()

	monsters = append(monsters, NewMonster(float32(MAP_WIDTH)-100, float32(MAP_HEIGHT)-100))

	for {
		elapsed_time := time.Since(start_time).Milliseconds()
		// monster_spawn_time := time.Since(monster_start_time).Seconds()

		if elapsed_time > time.Second.Milliseconds()/int64(FPS) {

			player_new_pos_buf := make([]byte, 1024)
			n, retAddr, err := udpConn.ReadFromUDP(player_new_pos_buf)
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
				monster.UpdatePosition(player)
				formatted, err := monster.bufferFormat()
				if err != nil {
					log.Println("Error while formatting monster : ", err)
					continue
				}

				output_infos = slices.Concat(output_infos, formatted.Bytes())
			}
			for _, projectile := range projectiles {
				projectile.UpdatePosition()
				formatted, err := projectile.bufferFormat()
				if err != nil {
					log.Println("Error while formatting projectile : ", err)
					continue
				}
				output_infos = slices.Concat(output_infos, formatted.Bytes())
			}

			output_with_len := new(bytes.Buffer)
			err = binary.Write(output_with_len, binary.LittleEndian, uint16(len(output_infos)))
			output_with_len.Write(output_infos)

			_, err = udpConn.WriteToUDP(output_with_len.Bytes(), retAddr)
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
