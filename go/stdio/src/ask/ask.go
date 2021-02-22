package ask

import (
	"bufio"
	"os"
	"strings"
)

var r = bufio.NewReader(os.Stdin)

func Ask(prompt string) string {
	os.Stdout.WriteString(prompt)
	var err error
	var isPrefix bool
	var nLine []byte
	var rawLine []byte

	rawLine, isPrefix, err = r.ReadLine()
	checkError(err)

	if isPrefix {
		for {
			if (isPrefix) {
				nLine, isPrefix, err = r.ReadLine()
				checkError(err)
				rawLine = append(rawLine, nLine...)
			} else {
				break
			}
		}
	}

	return strings.ToLower(string(rawLine))
}

func checkError(err error) {
	if err != nil {
		os.Stdout.WriteString(err.Error())
		os.Exit(1)
	}
}
