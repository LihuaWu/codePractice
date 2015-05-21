package main

func main() {
	var a int
	var b int32
	a = 15
	b = a + a //会引发一个编译错误，主要是由于混用这些类型向变量赋值导致。
	b = b + 5
}
