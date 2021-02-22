// bubblesort_test.go
package bubblesort

import "testing"

func TestQS1(t *testing.T) {
	val := []int{5,4,3,2,1}
	BubbleSort(val)
	if val[0] != 1 || val[1] != 2 || val[2] != 3 || val[3] != 4 || val[4] != 5 {
		t.Error("faild, need 1 2 3 4 5, got", val)
	}
}

func TestQS2(t *testing.T) {
	val := []int{5,5,4,2,1}
	BubbleSort(val)
	if val[0] != 1 || val[1] != 2 || val[2] != 4 || val[3] != 5 || val[4] != 5 {
		t.Error("failed, need 1 2 4 5 5, Got", val)
	}
}

func TestQS3(t *testing.T) {
	val := []int{1}
	BubbleSort(val)
	if val[0] != 1 {
		t.Error("failed, need 1, got", val)
	}
}
