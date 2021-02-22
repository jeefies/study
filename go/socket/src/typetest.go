package main

import "fmt"

func main() {
	str := "Some string"
	bytes := []byte(str)
	nstr := string(bytes)
	fmt.Println(nstr)
}
