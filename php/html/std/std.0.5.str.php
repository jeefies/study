<?php
	function n() {
		echo '<br>';
	}
	$str1 = 'I Like PHP';
	$str2 = '$str1';
	$str3 = "$str1";
	echo $str1.'<br>'.$str2.'<br>'.$str3.'<br>';
	echo <<<std
<font color='#FF0099'> $str1, Jeef</font>
std;
	n();
	$str = '  \r\r(:something)\n\b  ';
	echo trim($str).'     trim($str, \'\r\r(: :)\')'.trim($str, "\r\r(: :)");
	echo '<br>';
	echo 'origin str'.$str.'<br>';
	n();
	$str = 'some thing " and some \' params';
	echo 'str'.$str;
	n();
	$slash = addslashes($str);
	echo 'addslashes(str)'.$slash.'<br>';
	echo 'stripslashes(slash)'.stripslashes($slash);
	echo '<br>';
	n();
	$str = '  some  ';
	echo ltrim($str).':ltrim   rtrim:'.rtrim($str);
	echo '<br><br>';
	$str2 = 'get length';
	echo 'get len of str: '.$str2;
	echo '<br>';
	echo 'len:'.strlen($str2);
	echo '<br>';
	$str3 = 'She is a well-kown person';
	echo substr($str3, 0);
	echo '<br>';
	echo substr($str3, 4, 10);
	n();
	echo substr($str3, -5, 4);
	n();
	echo substr($str3, 0, -4);
	n();n();
	
	$form = <<<fom
<form method="post" action='std.0.5.str.php' encrypt='multipart/form-data'>
	<input type='hidden' name='action' value='upload' />
	<input type='file' name='ufile' />
	<input type='submit' value='upload'>
</form>
fom;
	echo $form;
	if (isset($_POST['action']) && $_POST['action'] == 'upload') {
		echo "uploading  ";
		$bfile = './uploads/';
		$pic_name = $_POST['ufile'];
		echo $pic_name;
		$extension = strstr($pic_name, '.');
		if ($extension != '.py') {
			echo "<script>alert('error type of file, need py file'); window.location.href='std.0.5.str.php';</script>";
			#echo "error type of file, need .py file";
		} else {
			n();
			echo 'upload success';
		}
		n();
		#echo "not matched extension: ";
		#if ($extension != '') {
		#	echo $extension;
		#} else {
		#	echo 'none';
		#}
		#n();
		#echo $pic_name;
		//echo 'get file '.$pic_name;
	}
?>
