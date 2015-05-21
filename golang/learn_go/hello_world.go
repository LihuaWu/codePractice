package main

import "fmt"

//Print something
//在Go中， package总是首先出现，然后是import, 然后是其它内容。
//当Go程序在执行的时候，首先调用的函数是main.main(),这是从C中继承而来。
//字符串用"包裹，并且可以包含非ASCII的字符。
//编译时使用go build xx.go就可以。会生成同名的可执行文件。

func main() {
	fmt.Println("Hello, world; 我的世界")
}

