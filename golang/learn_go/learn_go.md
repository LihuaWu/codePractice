Go语言学习笔记
==============

#### Go中的变量、类型和关键字

Go在语法上有类似C的感觉，如果希望将两个或更多的语句放在一行书写，它们必须使用分号；进行分隔。一般情况下，则不需要使用分号。

Go同其它语言不同的地方在于变量的类型在变量名的后面。

如

	a int

当定义了一个变量时，它默认赋值为其类型的null值。即

	var a int  // a = 0

在Go中，声明和赋值是两个过程，但是可以连在一起。如:

	var a int	 	a := 5
	var b bool		b := false
	a = 15
	b = false

多个var声明可以成组；const和import同样允许这么做。如：

	var (
		x int
		b bool
	)

有相同类型的多个变量同样可以在一行内完成声明
	
	var x, y int	//让x和y都是int类型变量。

同样可以使用平行赋值:

	a, b := 20, 16 //让a和b都是整数变量。

一个特殊的变量名是_。任何同仁给它的值都被丢弃。

	_, b := 34, 45

Go的编译器对声明却未使用的变量在报错。

##### 布尔类型
bool true/false

##### 数字类型

int, 这个类型根据你的硬件决定适当的长度。(32位的硬件上是32位的，64位的硬件上是64位的)

如果希望明确其长度，可以使用int32, int64。

完整的整数类型列表是(int8, int16, int32, int64, byte, uint8, uint16, uint32, uint64)。byte是uint8的别名。

浮点类型的值有float32和float64, 没有float类型。64位的整数和浮点数总是64位的，即便是在32位的架构上。

混用不同类型的变量赋值会引起编译器错误。

赋值可以使用八进制、十六进制或科学计数法:077, 0xFF, 1e3。

##### 常量

常量在编译时被创建，只能是数字，字符串或布尔值；可以使用iota生成枚举值。

const (
	a = iota //第一个iota表示0
	b = iota //此时iota的值增加1。此时也可以省略 = iota
) 

##### 字符串

字符串在Go中是UTF-8的，由双引号包裹的字符序列。如果使用单引号，则表示一个字符（UTF-8编码）,这种在Go中不是string。

一旦给变量赋值，字符串就不能修改了, 在Go中字符串是不可变的。

在Go中修改字符串需要下面的方法：

	s := "hello"
	c := []rune(s)
	c[0] = 'c'
	s2 := string(c)
	fmt.Printf("%s\n", s2)

多行字符串的书写

	s := "Starting part"
		+ "End part"

会被转化为

	s := "Starting part";
		+ "Ending part"; 

这是错误的，应当写成:

	s := "Starting part" +
	 	"Ending part"

或者书写时使用反引号`

	s := `Starting part // s现在包含换行,在引号内的字符不转义。
		Ending part`

##### rune

Rune是int32的别名，用UTF-8进行编码。当需要遍历字符串中的字符时，使用。可以循环每个字节。

##### 复数

##### 错误

	var e error // 定义了一个error类型的亦是，其值为nil。这个error类型是一个接口。

##### 内建函数

close
	用于channel通讯。使用它来关闭channel。

delete
	用于在map中删除实例。

len和cap
	len用于返回字符串，slice和数组的长度。	

new
	用于各种类型的内存分配。

make
	用于内建类型(map, slice, channel)的内存分配。

copy
	用于复制slice。

append
	用于追加slice。

panic和recover
	用于异常处理机制。

print和println
	底层打印函数。

complex, real和imag
	全部用于处理复数。

##### array

array由[n]<type> 定义,n标示array的长度，而<type>标示希望存储的内容的类型。对array的元素赋值或索引是由方括号完成的。

	var arr [10]int
	arr[0] = 42
	arr[1] = 43

像var arr = [2]int这样的数组类型有固定的大小。大小是类型的一部分。由于不同的大小是不同的类型，因此不能改变大小。数组同样是值类型的，将一个数组赋值给另一个数组，会复制所有的元素。尤其是当向函数内传递一个数组的时候，它会获得一个数组的副本，而不是数组的指针。

同时可以使用如下来定义并初始化一个数组
	
	a := [3]int {1, 2, 3}

也可以简写为
	
	a := [...]int{1, 2, 3} //Go会自动统计元素的个数。

多维数组可以简写为:

	a := [3][2]int {{1,2}, {3,4}, {5,6}}

##### slice

slice与array接近，但是在新的元素加入的时候可以增加长度。slice总是指向底层的一个array。这是其与array不同的地方；slice是引用类型，这意味着当赋值某个slice到另外一个变量，两个引用会指向同一个array。

一个固定长的array会影响slice的容量和长度。 len(slice)为其所指向的array的长度，cap(slice)为剩余的array未被slice表示的长度。















	

