proc newline {} {
	puts ""
}

set x "a b c"
puts "Item 2 in x ($x) should be [lindex $x 1]"

newline

set y "1/234/54/3"
puts {split y by '/' use [split $y "/"]}
set ys [split $y "/"]
puts "now splitted y is: '$ys', index 2 should be [lindex $ys 2]"
puts "It's length is [llength $ys]"

newline

set z [list puts "arg ys is $ys"]
puts "list can make a list of the arguments"
puts {we do `set z [list puts "arg ys is $ys"]`}
puts "now , z is '$z'"

newline

puts "for each just like a for loop, but different!"
set i 0
foreach j $ys {
	puts "index $i in list ys is $j"
	incr i
}

newline

set a [list a b {c d e} {f {g h}}]
puts "List a is: $a"

newline

set a [split $a]
puts "Splited a is: $a"
# default to split by " "
foreach i $a {
	puts "Each items are: $i"
}

newline

set a [concat a b {c d e} {f {g h}}]
puts {now set a [concat a b {c d e} {f {g h}}]}
puts "a turn to: $a"
foreach i $a {
	puts "Each items are: $i"
}

newline

lappend a {h i}
puts "append a with {h i}, notice {h i} is a single item"
puts "now a is : $a"

newline

set a [linsert $a 2 {cc dd}]
puts "insert {cc dd} to a with index 2"
puts "now it turns to: $a"

newline

set a [lreplace $a 2 4 A B]
puts "replace index 2 and 3 to A B"
puts "a is : $a"

newline

# need no set
lset a 2 "C"
puts "set index 2 to C"
puts "a to : $a"

set chars [split "abcdefghij" ""]
set list ""
for {set i 0} {$i < 10} {incr i} {
	lappend list "[expr {10 - $i}] [lindex $chars $i]"
}
puts "$list"

set list [lsort $list]
puts "$list"
# include index 3 and 5
puts "range 3 - 5 are: [lrange $list 3 5]"

set li [list {Jeefy 123} {Michael 542} {Silvia 907} {Billyy 8} {Billy 09}]
# notice the search method is not to search the key but to match the whole item
# There's no Key in list, but array.
# So if you want to get Billy right, you should use command below
# Like [lsearch $li "Billyy *"] is also for match Billyy ^_^
puts "[lsearch $li Mi*] [lsearch $li "Billy *"]"
