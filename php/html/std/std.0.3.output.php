<?php
	$i = 'i\'s ctx';
	echo $i;
	echo '<br>'; //Change a row
	echo "echo \"\$i\" = $i";
	echo '<br>';
	echo 'echo "$i" = $i';
	// another way to echo out
	echo <<< std
Here is no differences between echo with to " , \$i can echo out too, echo as '$i'
std;
?>
