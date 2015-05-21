package main

func printArray(s []int) {
	for _, v := range s {
		print(v, " ")
	}
	println()
}

func printA(s [2]int) {
	for _, v := range s {
		print(v, " ")
	}
	println()
}

func main() {

	a := [2]int {1, 2}

	s2 := make([]int, 2)
	s2 = a[:]

	printA(a)
	printArray(s2)
	s3 := append(s2, 3)
	s2[0] = 10000

	printA(a)
	printArray(s2)
	printArray(s3)

	println(len(s2), cap(s2))

	var b [100]int
	sb := make([]int, 5)
	sb = b[2:4]

	println(len(sb), cap(sb))
	printArray(sb)
}

