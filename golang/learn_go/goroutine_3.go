package main

import "fmt"

func main() {
	ch := make(chan string)
	go func() {
		ch <- "Hello!"
		close(ch)
	}()
	fmt.Println(<-ch)
	fmt.Println(<-ch)
	fmt.Println(<-ch)
	fmt.Println(<-ch)
	fmt.Println("-----")
	v, ok := <-ch
	fmt.Printf("ok=%e, v=%s\n", ok, v)
}

