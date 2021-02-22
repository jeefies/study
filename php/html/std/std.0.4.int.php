<?php
	$i1 = 1234567890;
	// with base 10
	$i2 = 0x1234567890;
	// with base 16
	$i3 = 01234567;
	// base 8 int can have numbers bigger than 7 appear when define the arg
	// or the function would not be used
       	// with base 8
	$i4 = 01234567;
       	// with base 8
	// base 8 int start with 0
	echo 'int with base 10: '.$i1.'<br>';
	echo 'int with base 16: '.$i2.'<br>';
	echo 'int as base 8: ';
	if ($i3 == $i4) {
		echo 'int3 = int4 = '.$i3;
	} else {
		echo 'int3 != int4';
	}
?>
