proc newline {} {
	puts ""
}

set f [open "newfile.tmp" w]

puts $f "Here's the first line"
puts $f "Another one here"

close $f

set f [open "newfile.tmp" r]

gets $f line1

puts "close and then read:"
puts "$line1"

newline

seek $f 3
puts "seek f to 3 and then read:"
puts "[gets $f]"
puts "now it's at [tell $f]"

newline

if {[eof $f] == 1} {
	puts "Reach end of file now"
} else {
	puts "There's still something remaining:"
	puts [read $f]
}

newline

puts {we use [file delete ...] to delete a file}
file delete "newfile.tmp"

# file path ops
newline

# nativename returns the native name of the file or directory
set path [file nativename [file join / home pi study tcl plain-tcl]]
set files [file nativename [file join "." "hello-world.tcl"]]
puts "File Path: $files"
puts "Path: $path"

newline

puts "Dirname of file's: [file dirname $files]" ;# should be .
puts "Tail of file's: [file tail $files]" ;# should be hello-world.tcl
puts "Rootname of file's: [file rootname [file tail $files]]" ;# should be hello-world, if without tail, it should be ./hello-world
puts "Extension name of file's: [file extension $files]" ;# should be .tcl
puts "Split path: [file split $path]" ;# should be "home pi study tcl plain-tcl"

newline

puts "Info about the file $files:"
puts "Exists ? [file exists $files]"
puts "Last access time: [file atime $files]"
puts "Last modify time: [file mtime $files]"
puts "Size: [file size $files]"
puts "Executable ? [file executable $files]"
puts "File ? [file isfile $files]"
puts "Directory ? [file isdirectory $files]"
puts "Readable ? [file readable $files]"
puts "Writeable ? [file writable $files]"
puts "Owned ? [file owned $files]"
puts {Link path ? ! it's not a link, so [file readlink $files] would cause error!}
# puts "Link ? [file readlink $files]"
#
# file 				- normal file
# directory 		- directory
# characterSpecial 	- Character oriented device 
# blockSpecial 		- Block oriented device
# fifo 				- Named pipe
# link 				- Symbolic link
# socket 			- Named socket
puts "Type: [file type $files] (It's \"[file type $path]\" of \$path)"

newline

puts "There are two arrays of file's status:"
puts "One is lstat"
puts "Another is stat"
puts "lstat would not get the information of the file linked to if it's a link, but the link itself"

# file move delete copy and rename
file mkdir tmp
puts "Create dir `tmp` ? [file isdirectory tmp]"
file delete tmp
puts "Delete dir `tmp` ? [file exists tmp]"
puts "\tIf we want to delete a dir with somthing in, we should use `-force` option"
file copy "hello-world.tcl" "hello.tcl"
puts "We copy hello-world.tcl to hello.tcl: [file isfile hello.tcl]"
file rename -force "hello.tcl" "hello-world.tcl"
puts "We rename hello.tcl back to hello-world.tcl with -force option"
puts "So there's no hello.tcl any more!"
