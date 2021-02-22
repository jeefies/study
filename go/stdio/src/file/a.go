package main

import (
	"path"
	"os"
	"io/ioutil"
	"fmt"
	"center"
//	"io"
//	"time"
)

func main() {
	fmt.Println(cent("APart 1"))
	// APart 1, ioutil.ReadDir(path string) => A sequence of os.FileInfo and a error ([]os.FileInfo, error)
	fileInfos, _ := ioutil.ReadDir("../")
	var mode os.FileMode
	for index, info := range fileInfos {
		fmt.Print(index, " ", info.Name())
		// Info attrs: 
		// string info.Name(); int64 info.Size(); FileMode info.Mode()
		// time.Time() info.ModTime; bool info.IsDir(); interface{} Sys()
		mode = info.Mode()
		// Mode attrs:
		// bool mode.IsDir(); bool mode.IsRegular(); ?? mode.Perm
		fmt.Print(" ", mode.IsDir(), " ")
		perm := mode.Perm()
		fmt.Printf("%T ", perm)
		fmt.Printf("%s ", perm)
		fmt.Print(mode.String())
		fmt.Println()
	}
	fmt.Println(cent(""))

	fmt.Println("\n\n" + cent("APart 2"))

	// APart 2, ioutil.TempDir(path, pattern string) => (string, error)
	APart2()

	fmt.Println(cent(""))
	fmt.Println("\n\n")
	Main()
}

func APart2() {
	// TempDir and TempFile
	parentDir := os.TempDir() //== "/tmp"
	var tempName string = "Example"
	var tempDir string = path.Join(parentDir, tempName)

	fmt.Println("Parent Dir:", parentDir)
	tempDir, err := ioutil.TempDir(parentDir, tempName)
	checkError(err)

	defer os.RemoveAll(tempDir)
	// time.Sleep(5e9)  For 5 seconds
	fmt.Println(tempDir)

	var fileName string = "temp.name"
	var tempFile *os.File
	tempFile, err = ioutil.TempFile(tempDir, fileName)
	checkError(err)

	defer func() {
		fmt.Println("RemoveAll")
		tempFile.Close()
	}()

	_, err = tempFile.WriteString("A temp File!!!")
	checkError(err)

	fmt.Println("\t" + cent("APart 3"))
	APart3(tempFile, tempDir)
	fmt.Println("\t" + cent(""))

}

func APart3(tmpFile *os.File, tmpPath string) {
	fmt.Print("\t")
	// It's an absolute file path
	var filePath = tmpFile.Name()
	// ioutil.ReadFile(filename) ([]byte, error)

	content, err := ioutil.ReadFile(filePath)
	checkError(err)

	/*  Can not read from the origin file!
	ctt := make([]byte, 0, 50)
	_, err = tmpFile.Seek(0, 0)
	checkError(err)
	_, err = tmpFile.Read(ctt)
	checkError(err)

	fmt.Println("\ttempRead: ", ctt)
	*/

	fmt.Print("\tioutil ReadFile:\n\t\t")
	os.Stdout.Write(append(content, 10))
}

func checkError(err error) {
	if err != nil {
		fmt.Fprintf(os.Stderr, "Fatal Error: %s", err.Error())
		os.Exit(1)
	}
}

func cent(str string) string {
	return center.Center(str, 60, '-')
}
