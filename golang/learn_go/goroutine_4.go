package main

import "fmt"

type Sushi string

func main() {
	var ch <- chan Sushi = Producer()
	for s := range ch {
		fmt.Println("Consumed", s)
	}
}

func Producer() <-chan Sushi  {
	ch := make(chan Sushi)
	go func() {
		ch <- Sushi("my world.")
		ch <- Sushi("toro nigiri")
		close(ch)
	}()
	return ch
}
