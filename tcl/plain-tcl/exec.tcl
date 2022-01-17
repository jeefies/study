set tmpDir "/tmp"
if { [info exists ::env(TMP)] }  {
	set tmpDir $::env(TMP)
}

set tmpFile [file join $tmpDir "tmp_run_[pid].tcl"]

set fp [open $tmpFile w]
puts $fp {
	gets stdin line
	puts "You have input: $line"
	exit 0
}

flush $fp

# open a io pipe for the running program!
# puts [info nameofexecutable] tclsh
set io [open "|[info nameofexecutable] $tmpFile" r+]
puts $io "Here are the input!"
flush $io

set len [gets $io line]
puts  "To send: 'Here are the input!'"
puts "Received is: '$line'"
puts "The line is $len characters long"


# Here we now use exec command to run another program
# I am confused when running this!
set fn "hello-world.tcl"
set tmpio [open [file join $tmpDir "tmpio.tmp"] w+]
if {[file exists $fn] == 1} {
	exec tclsh $fn >@ $tmpio
	puts "Program running..."
	puts "Reading:"
	seek $tmpio 0
	puts "[read $tmpio]"
} else {
	puts "Program file not exists"
}

file delete $tmpio $tmpFile
