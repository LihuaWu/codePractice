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

func types() {
		a, b := 1, "hello"
//	work()
	log.Println(a, b)
	const (
		c = iota
		d string = "hello"
		e = iota
		f = 1
		g = iota + 6
	)
	log.Println(c, d, e, f, g)
	var h complex64 = 5 + 5i;
	log.Printf("value is %v", h)

	list := []string {"a", "b", "c"}
	for k, v := range list {
		log.Println(k, "-", v)
	}

	slice := make([]string, len(list) - 1)
	copy(slice, list[1:])

	slice[1] = "d"
	for k, v := range list {
		log.Println(k, "-", v)
	}
	s2 := append(list, "e")
	s2[2] = "ggg"
	for k, v := range s2 {
		log.Println(k, "-", v)
	}
	for k, v := range list {
		log.Println(k, "-", v)
	}

}

func Questions() {
	for i := 0; i < 10; i++ {
		log.Printf("%d ", i + 1)
	}
	log.Println()

	sum := 0
	for i := 0; i < 10; i ++ {
		sum += i
	}
	sum /= 10
	println(sum)

}

func main() {
	Questions()
}
