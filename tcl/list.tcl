set x "a b c"
puts "Item 2 in x ($x) should be [lindex $x 1]"

set y "1/234/54/3"
puts {split y by '/' use [split $y "/"]}
set ys [split $y "/"]
puts "now splitted y is: '$ys', index 2 should be [lindex $ys 2]"
puts "It's length is [llength $ys]"

set z [list puts "arg ys is $ys"]
puts "list can make a list of the arguments"
puts {we do `set z [list puts "arg ys is $ys"]`}
puts "now , z is '$z'"

puts "for each just like a for loop, but different!"
set i 0
foreach j $ys {
	puts "index $i in list ys is $j"
	incr i
}
