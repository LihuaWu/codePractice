package main

import "fmt"
import "sync"

func race() {
	wait := make(chan struct{})
	n := 0
	go func() {
		n++
		close(wait)	
	}()
	n++
	<-wait
	fmt.Println(n)
}

// Don't communicate by sharing memory;
// share memory by communicating.
func SharingIsCaring() {
	ch := make(chan int)
	go func() {
		n := 0
		n++
		ch <- n
	}()
	n := <-ch
	n++
	fmt.Println(n)
}

type AtomicInt struct {
	mu	sync.Mutex
	n 	int
}

func (a *AtomicInt) Add(n int) {
	a.mu.Lock()
	a.n += n
	a.mu.Unlock()
}

func (a *AtomicInt) Value() int {
	a.mu.Lock()
	n := a.n
	a.mu.Unlock()
	return n
}

func lockItUp() {
	wait := make(chan struct{})
	var n AtomicInt
	go func() {
		n.Add(1)
		close(wait)	
	}()
	n.Add(1)
	<-wait
	fmt.Println(n.Value())
}


func main() {
	lockItUp()
}
