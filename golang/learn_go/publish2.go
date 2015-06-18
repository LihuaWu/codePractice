package main

import "fmt"
import "time"

func main() {
	wait := Publish("Channels let goroutines communicate.", 5 * time.Second)
	fmt.Println("waiting for news...")
	<-wait
	fmt.Println("The news is out, time to leave.")
}

func Publish (text string, delay time.Duration) (wait <-chan struct{}) {
	ch := make(chan struct{})
	go func() {
		time.Sleep(delay)
		fmt.Println("BREAKING NEWS:", text)
		close(ch)
	}()
	return ch
}
