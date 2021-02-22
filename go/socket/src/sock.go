package main

import (
	"net"
	"os"
	"io"
	"bytes"
	"fmt"
)

const host string = "127.0.0.1"
const port string = "3000"

func main() {
	service := host + ":" + port

	conn, err := net.Dial("tcp", service)
	defer conn.Close()
	checkError(err)

	for{
		_, err = conn.Write([]byte("Hello!"))
		checkError(err)

		result, err := getResult(conn)
		checkError(err)
		var str string = string(result)
		fmt.Println(str)
	}

}

func checkError(err error) {
	if err != nil {
		fmt.Fprintf(os.Stderr, "Fatal error: %s", err.Error())
		os.Exit(1)
	}
}

func getResult(conn net.Conn) ([]byte, error) {
	result := bytes.NewBuffer(nil)
	var buf [1024]byte

	n, err := conn.Read(buf[0:])
	result.Write(buf[0:n])
	if err != nil {
		if err != io.EOF {
			return nil, err
		}
	}
	return result.Bytes(), nil
}
