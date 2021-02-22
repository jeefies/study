package main

import (
	"flag"
	"fmt"
	"bufio"
	"io"
	"os"
	"strconv"
	"time"
	"algorithm/qsort"
	"algorithm/bubblesort"
)

var infile *string = flag.String("i", "infile", "input file")
var outfile *string = flag.String("o", "oufile", "output file")
var algorithm *string = flag.String("a", "bubblesort", "algorithm for sort")

func readFile(infile string) (values []int, err error) {
	file, err := os.Open(infile)
	if err != nil {
		fmt.Println("Failed to open the file")
		return
	}

	defer file.Close()

	br := bufio.NewReader(file)
	values = make([]int, 0, 10)

	for {
		line, ispre, errr := br.ReadLine()

		if errr != nil {
			if errr != io.EOF {
				err = errr
			}
			break
		}

		if ispre {
			fmt.Println("A too large line")
			return
		}

		str := string(line)
		val, errr := strconv.Atoi(str)

		if errr != nil {
			err = errr
			return
		}

		values = append(values, val)
	}
	return
}

func writeFile(value []int, outfile string) error {
	file, err := os.Create(outfile)
	if err != nil {
		fmt.Println("Could not create the output file", outfile)
		return err
	}

	defer file.Close()

	for _, val := range value {
		str := strconv.Itoa(val)
		file.WriteString(str + "\n")
	}
	return nil
}

func main() {
	flag.Parse()

	if infile != nil {
		fmt.Println("infile: ", *infile, ", outfile: ", *outfile)
	} else {
		fmt.Println("infile is must given, use default infile")
	}

	val, err := readFile(*infile)
	if err == nil {

		ts := time.Now()

		switch *algorithm {
			case "bubblesort":
				bubblesort.BubbleSort(val)
			case "qsort":
				qsort.Qsort(val)
			default:
				fmt.Println("algorithm is unexpect, only in qsort or bubblesort")
			}
		te := time.Now()

		fmt.Println("sorting use time", te.Sub(ts))
		writeFile(val, *outfile)

	} else {
		fmt.Println(err)
	}
}
