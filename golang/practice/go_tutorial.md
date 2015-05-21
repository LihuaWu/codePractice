Go语言学习笔记
========================
####基础知识
1. Golang是一个使得程序员更加有效率的开源项目。Go是有**表达力、简洁、清晰和有效率**的。
它的并行机制使其很容易编写多核和网络应用。而新奇的**类型系统**允许构建有弹性的模块化程序。
Go编译到机器码非常快速，同时具有便利的垃圾回收和强大的运行时反射。Golang是快速的静态类型编译语言，
但是感觉上是动态类型的，解释型语言。
Go的一些特性使得Golang与众不同。
    1. 清晰并简洁
    2. 并行
    3. Channel
    4. 快速 
    5. 安全
    6. 标准格式化
    7. 类型后置
    8. UTF-8, 任何地方都是UTF-8的，包括字符串以及程序代码。
    9. 开源
    10. 开心
所有的Go文件以package <something>开头，对于独立运行的执行文件必须是package main
2. 变量， 类型， 关键字
        var a int
        var b bool
        a = 15
        b = false
        a := 15
许多个var声明可以成组
        var (
        x int
        b bool
        )
也可以平行赋值
        a, b := 34, 45
        a, b := 1, "hello world"
Golang会对声明未使用的变量报错。
    1. 布尔类型, true, false
    2. 数字类型, int根据硬件决定适当的长度。如果希望明确其长度，可以使用int32或者uint32。
byte是uint8的别名。
    3. 常量
            const (
                a = iota
                b = iota
            )
当iota再次在新的一行使用时，它的值增加了1。iota也可以省略使用。
iota值为其定义所在的行数，起始位置为0.

    4. 字符串， 内建类型是string, 一旦给变量赋值，字符串就不能修改了。在Go中字符串是不可变的。
            s := "hello"
            c := []rune(s)
            c[0] = 'c'
            s2 := string(c)
        对于多行字符串，写法如下所示:
            s := "starting part" + 
                "end part"
        rune是int32的别名，用UTF-8进行编码。一般在当需要遍历字符串中的字符时使用。可以
        循环每个字节。
    5. 错误，为了错误而存在的内建类型。叫error。error类型是一个接口。

3. 控制结构

    在Golang里面没有do while循环，只有for。有switch语句和if及select。无需圆括号，
而语句体必须总是包含在大括号内。
    Golang中的for循环有三种形式：
        for init; condition; post {}
        for condition {}
        for {}
    在for中执行多个变量，应当使用平行赋值，主要由于Go没有逗号表达式。

    range可以用于循环， 可以在slice, array, string, map和channel中使用。range是一个迭代器，
    当被调用时，从它循环的内容中返回一个键值对。
    当对slice或者array作循环时，range返回序号为键，这个序号对应的内容作为值。
    
    switch用法。略
4. 内建函数

    1. close, 用于channel通讯。用它来关闭channel。
    2. delete, 用于在map中删除实例。
    3. len和cap, len用于返回字符串，slice和数组的长度。
    4. new用于各种类型的内存分配。
    5. make用于内建类型(map, slice和channel)的内存分配。
    6. copy用于复制slice
    7. append用于追加slice
    8. panic和recover, 用于异常处理机制。
    9. print和println, 可以在不引入fmt包的情况下使用，主要用于调试。
    10. complex, real和imag， 全部用于处理复制。
5. array, slice和map的使用
    array 由[n]<type>定义，n标示array的长度，<type>标示希望存储的内容的类型。
    slice与array接近，但是在新的元素加入的时候可以增加长度。slice总是指向底层的一个array。
    slice是引用类型，是一个指向array的指针。对slice的修改会反映到底层的array上。
    如果需要在复本上进行修改，可以对原有的slice进行拷贝。
        list := []string {"a", "b", "c"}
        for k, v := range list {
                log.Println(k, "-", v)
        }
        slice := make([]string, len(list) - 1)
        copy(slice, list[1:])
        slice[1] = "d"
        for k, v := range list {
                log.Println(k, "-", v)
        }
    同理，使用append可以扩展slice。扩展后的append是在复本上进行append。
        s2 := append(list, "e")
        s2[2] = "ggg"
        for k, v := range s2 {
                log.Println(k, "-", v)
        }
        for k, v := range list {
                log.Println(k, "-", v)
        }
map类型 map[<from_type>]<to_type>
    1. 向map添加元素，m["k"] = 1
    2. 检查元素是否存在， value, present = m["k"]
    3. 删除元素 delete(m, "k")
)
