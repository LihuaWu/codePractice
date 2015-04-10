package main

import (
	"io"
	"fmt"
	"errors"
)

type Ustr string

func (s Ustr) Read(p []byte) (n int, err error) {
	i, ls, lp := 0, len(s), len(p)
	for ; i < ls && i < lp; i++ {
		if s[i] >= 'a' && s[i] <= 'z' {
			p[i] = s[i] + 'A' - 'a'
		} else {
			p[i] = s[i]
		}
	}
	switch i {
	case lp:
		return i, nil
	case ls:
		return i, io.EOF
	default:
		return i, errors.New("Read Fail")
	}
}

func main() {
	us := Ustr("Hello World!")
	buf := make([]byte, 32)
	n, err := io.ReadFull(us, buf)
	fmt.Printf("%s\n", buf)
	fmt.Println(n, err)

}
