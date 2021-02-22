package center

func Center(str string, size int64, fill rune) string {
	var i int64
	var rstr = []rune(str)
	var strs int64 = int64(len(str))
	var ls int64 = int64((size - strs) / 2.0)
	var rs int64 = size - ls - strs

	r := make([]rune, 0, size)

	for i = 0; i < ls; i++ {
		r = append(r, fill)
	}


	r = append(r, rstr...)

	for i = 0; i < rs; i++ {
		r = append(r, fill)
	}

	return string(r)
}
