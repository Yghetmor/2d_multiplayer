package main

import (
	"bytes"
	"encoding/binary"
	"log"
	"net"
)

func main() {
	var instances_map map[int] chan net.Conn

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

		go handleClient(conn, &instances_map)
	}
}

func handleClient(conn net.Conn, instances_map *map[int] chan net.Conn) {
	var buf []byte
	n, err := conn.Read(buf)
	if err != nil {
		log.Println("Error reading from connection : ", err)
		conn.Close()
		return
	}
	if n != 4 {
		log.Println("Error reading from connection : expected game session id (int) got packet of len : ", n, " instead")
		conn.Close()
		return
	}

	buf_reader := bytes.NewReader(buf)
	var session_number int
	err = binary.Read(buf_reader, binary.LittleEndian, &session_number)
	if err != nil {
		log.Println("Error reading session id : ", err)
		conn.Close()
		return
	}

	channel, ok := (*instances_map)[session_number]
	if ok {
		channel <- conn
	} else {
		(*instances_map)[session_number] = make(chan net.Conn)
		go StartInstance((*instances_map)[session_number], conn)
	}
}
