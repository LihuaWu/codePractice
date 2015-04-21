package main

import (
	"bufio"
	"fmt"
	"io"
	"io/ioutil"
	"os"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func ReadFile() {
	//Simple read content into memory from file.
	dat, err := ioutil.ReadFile("./rw.go")
	check(err)

	fmt.Print(string(dat))

	//to control which part to read from file
	f, err := os.Open("./rw.go")
	check(err)
	defer f.Close()

	//read 5 bytes
	b1 := make([]byte, 5)
	n1, err := f.Read(b1)
	check(err)
	fmt.Printf("%d bytes: %s\n", n1, string(b1))

	//continue to read following 2 bytes.
	o2, err := f.Seek(6, 0)
	check(err)
	b2 := make([]byte, 3)
	n2, err := f.Read(b2)
	check(err)
	fmt.Printf("%d bytes @%d: %s\n", n2, o2, string(b2))

	//using io package to continue reading.
	o3, err := f.Seek(6, 0)
	check(err)

	b3 := make([]byte, 4)
	n3, err := io.ReadAtLeast(f, b3, 4)
	check(err)

	fmt.Printf("%d bytes @%d: %s\n", n3, o3, string(b3))

	//roll back
	_, err = f.Seek(0, 0)

	//with buffer
	check(err)
	r4 := bufio.NewReader(f)
	b4, err := r4.Peek(5)
	check(err)
	fmt.Printf("5 bytes: %s\n", string(b4))

}

func WriteFile() {
	d1 := []byte("hello\ngo\n")
	//Simple write a string to file.
	err := ioutil.WriteFile("./dat1", d1, 0644)
	check(err)

	//big grain of control.
	f, err := os.Create("./dat2")
	check(err)
	defer f.Close()

	d2 := []byte{115, 111, 109, 101, 10}
	n2, err := f.Write(d2)
	check(err)
	fmt.Printf("wrote %d bytes\n", n2)

	n3, err := f.WriteString("writes\n")
	fmt.Printf("wrote %d bytes\n", n3)
	//write buffer into disk.
	f.Sync()

	//with buffer to write.
	w := bufio.NewWriter(f)
	n4, err := w.WriteString("buffered\n")
	fmt.Printf("wrote %d bytes\n", n4)
	//make sure all cached content are written to disk
	w.Flush()
}

func main() {
	//	ReadFile()
	WriteFile()
}
