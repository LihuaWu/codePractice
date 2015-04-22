package main

import (
	"log"
	"net"
	"os"
//	"fmt"
)

const (
	a = iota
	b string = "hello world"
)

func work() {
	var port string = ":" + os.Args[1]
	ln, err := net.Listen("tcp", port)
	if err != nil {
		log.Println(err)
		return
	}
	for {
		conn, err := ln.Accept()
		if err != nil {
			log.Println(err)
			continue
		}

		go echoFunc(conn)
	}
}

func echoFunc(c net.Conn) {
	buf := make([]byte, 1024)

	for {
		n, err := c.Read(buf)
		if err != nil {
			log.Println(err)
			return
		}

		c.Write(buf[:n])
	}
}

func main() {
	log.Printf("%d %s\n", a, b)
//	work()
}
