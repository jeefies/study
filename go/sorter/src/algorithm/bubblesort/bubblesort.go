// bubblesort.go
package bubblesort

func BubbleSort(val []int) {
	flag := true

	for i := 0; i < len(val) - 1; i++ {
		flag = true

		for j := 0; j < len(val) - i - 1 ; j++ {
			if val[j] > val[j + 1] {
				val[j], val[j + 1] = val[j + 1], val[j]
				flag = false
			}
		}

		if flag == true {
			break
		}
	}
}

