package main

import (
	"bytes"
	"encoding/binary"
	"log"
	"net"
)

func main() {
	instances_map := make(map[int]chan net.Conn)

	listener, err := net.Listen("tcp", "localhost:6969")
	if err != nil {
		log.Fatal("Error listening on port : ", err)
	}
	defer listener.Close()

	log.Println("Listening on port 6969...")

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Println("Got an error listening : ", err)
			continue
		}

		log.Println("Got a connection !")
		go handleClient(conn, &instances_map)
	}
}

func handleClient(conn net.Conn, instances_map *map[int]chan net.Conn) {
	buf := make([]byte, 256)
	for {
		n, err := conn.Read(buf)
		if err != nil {
			log.Println("Error reading from connection : ", err)
			conn.Close()
			return
		}

		if n == 4 {
			break
		}
	}

	buf_reader := bytes.NewReader(buf)
	var session_number int32
	err := binary.Read(buf_reader, binary.LittleEndian, &session_number)
	if err != nil {
		log.Println("Error reading session id : ", err)
		conn.Close()
		return
	}

	channel, ok := (*instances_map)[int(session_number)]
	if ok {
		channel <- conn
	} else {
		(*instances_map)[int(session_number)] = make(chan net.Conn)
		log.Println("Creating instance no : ", session_number)
		go startInstance((*instances_map)[int(session_number)], conn)
	}
}
