package main

import (
	"C"
	"fmt"
)

var explain = "the explain //export Fib is must has"

//export Fib
func Fib(n uint64) int {
	if n == 1 || n == 2 {
		return 1
	} else {
		return Fib(n - 1) + Fib(n - 2)
	}
}

func main() {
	var r = Fib(40)
	fmt.Println(r)
}
