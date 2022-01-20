lappend auto_path [file normal .]
package require scurl

set r [urlget tcl.tk]
puts "$r"
puts "Get tcl.tk ok\n"

set r [urlget https://gitee.com]
puts "Can get https://gitee.com:"
puts [string range $r 0 100]
puts ""

set r [urlget https://github.com]

puts "get github.com:"
puts "$r"
puts "\nget github.com ok\n"
