package main

import "fmt"
import "sync"

func race() {
	var wg sync.WaitGroup
	wg.Add(5)

	for i := 0; i < 5; i++ {
		go func() {
			fmt.Print(i)
			wg.Done()	
		}()
	}
	wg.Wait()
	fmt.Println()	
}

func main() {
	race()
}
