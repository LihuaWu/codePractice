package main

import (
	"fmt"
)

func RandomBits() <-chan int {
	ch := make(chan int)
	go func() {
		for {
			select {
				case ch <- 0:
				case ch <- 1:
			}
		}
	}()
	return ch
}

func main() {
	ch := RandomBits()
	for i := 10; i > 0; i-- {
		fmt.Print(<- ch)
	}
	fmt.Println()
}
