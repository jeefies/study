package main

/*
void pcgo() {
	printf("In c: Hello cgo\n");
}

*/
import "C"
import "os"

func main() {
	os.Stdout.Write("Hello Cgo\n")
	os.Stdout.Sync();
	C.pcgo();
}
