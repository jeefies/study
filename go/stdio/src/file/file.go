package main

import (
	"io/ioutil"
	"os"
	"fmt"
	"ask"
)


func Main() {
	fmt.Println(cent("Part 1"))
	Part1() // ioutil.ReadDir
	fmt.Println(cent(""))
	fmt.Println("")
	fmt.Println(cent("Part 2"))
	Part2() // TempDir and TempFile
	fmt.Println(cent(""))
	fmt.Println("")
//	Part3()  ioutil.ReadFile
	fmt.Println(cent("Part 4"))
	Part4() // os.Open, os.OpenFile()
	fmt.Println(cent(""))
	fmt.Println("")
	fmt.Println(cent("Part 5"))
	Part5()
	fmt.Println(cent(""))
	fmt.Println("")
	ans := ask.Ask("Remove Generated files? [Yes/No]: ")
	switch ans {
		case "yes":
			fallthrough
		case "y":
			removeGen()
		default:
			fmt.Println("Keep Generated File")
		}
}

func Part1() {
	var err error
	var fileInfos []os.FileInfo
	fileInfos, err = ioutil.ReadDir("./")
	checkError(err)

	var info os.FileInfo
	for _, info = range fileInfos {
		fmt.Println("Name:", info.Name())
		fmt.Println("Size:", info.Size())
		fmt.Println("Time:", info.ModTime())
		fmt.Println("IsDir:", info.IsDir())
		fmt.Println()
	}
}

func Part2() {
	var err error
	var parentDir string = os.TempDir()
	const tempDirName string = "example"
	const tempFileName string = "tmp.file"
	fmt.Print("Parent Dir:", parentDir)

	var tempDir string
	tempDir, err = ioutil.TempDir(parentDir, tempDirName)
	checkError(err)

	defer os.RemoveAll(tempDir)
	fmt.Println("Temp Dir Path:", tempDir)

	var tempFile *os.File
	tempFile, err = ioutil.TempFile(tempDir, tempFileName)
	checkError(err)
	fmt.Println("Temp File Path:", tempFile.Name())
	defer tempFile.Close()

	var ctt string = "This is a Temp File"
	var byte_ctt []byte = []byte(ctt)
	tempFile.Write(byte_ctt)

	Part3(tempFile)
}

func Part3(tmpFile *os.File) {
	var path string = tmpFile.Name()

	var content []byte
	var err error
	content, err = ioutil.ReadFile(path)
	checkError(err)

	os.Stdout.Write(append(content, 10))
}

func Part4() {
	const fileName = "./test.txt"
	var stat os.FileInfo
	var err error

	// Remove exists File
	stat, err = os.Stat(fileName)
	if err != nil {
		if os.IsExist(err) {
			os.Remove(fileName)
		}
	} else {
		os.Remove(fileName)
	}

	// Use OpenFile to Create a new File(not force)
	var wfile *os.File

	wfile, err = os.OpenFile(fileName, os.O_WRONLY|os.O_CREATE, 0733)
	checkError(err)
	defer wfile.Close()

	wsize, err := wfile.WriteString("Test File 2")
	checkError(err)
	fmt.Printf("Write in %d bytes\n", wsize)

	// Use Open to Read a File
	var file *os.File
	file, err = os.Open(fileName)
	checkError(err)
	stat, err = file.Stat()
	checkError(err)
	fsize := stat.Size()
	defer file.Close()

	var filec []byte = make([]byte, 0, fsize)
	file.Read(filec)

	os.Stdout.Write(filec)

	// Use OpenFile to append some data
	var afile *os.File
	afile, err = os.OpenFile("./test.txt", os.O_APPEND|os.O_WRONLY, 0733)
	checkError(err)
	defer afile.Close()

	asize, err := afile.Write([]byte("\nA new Line"))
	checkError(err)
	fmt.Printf("Append in %d bytes\n", asize)
}

func Part5() {
	// Use OpenFile Read Only to read a file
	// Didn't succeed
	var rfile *os.File
	var err error
	rfile, err = os.OpenFile("./test.txt", os.O_RDONLY, 0733)
	checkError(err)
	defer rfile.Close()

	stat, err := rfile.Stat()
	checkError(err)
	var n_rsize int64 = stat.Size()
	fmt.Printf("File Size: %d\n", n_rsize)
	var bytearray []byte = make([]byte, 0, n_rsize)
	rfile.Seek(0, 0)
	_, err = rfile.Read(bytearray)
	checkError(err)
	fmt.Println(bytearray)
	os.Stdout.Write(append(bytearray, 10))
}

func removeGen() {
	var err error = os.Remove("./test.txt")
	checkError(err)
}

/*
func Print(str string) {
	os.Stdout.Write([]byte(str))
}

func Println(str string) {
	os.Stdout.Write([]byte(str))
	os.Stdout.Write(byte(10))
}

func itos(i int) string {
	var nums []byte = []byte{48, 49, 50, 51, 52, 53, 54, 55, 56, 57}
	res = make([]byte, 0, 1)
	for {
		res = append(res, nums[i % 10])
		i /= 10
		if i < 10 {
			res = append(res, nums[i])
			break
		}
	}

	return string(res)
}
*/
