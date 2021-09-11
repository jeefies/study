package main

import ("fmt"
	"os"
	"strconv"
)

func isUgly(n int) bool {
    for {
        if n % 5 == 0 {
            n /= 5
        } else {
			break
		}
    }
    for {
        if n % 3 == 0 {
            n /= 3
        } else {
			break
		}
    }
    for {
        if n % 2 == 0 {
            n /= 2
        } else {
			break
		}
    }
	if n == 1 {
		return true
	}
	return false
}

func main() {
	nums, _ := strconv.Atoi(os.Args[1])
	r := isUgly(nums)
	fmt.Println(r)
}
