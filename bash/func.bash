gps() {
	fn=`mktemp XXXXXXXXXX`
	ps -elf > $fn
	cat $fn
	rm $fn
}
