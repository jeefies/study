proc newline {} {
	puts ""
}

set str "Some chars here"
set str2 "Here are another string"

puts "var str is \"$str\""
puts "Length : [string length $str]"
puts "4th char: [string index $str 3]"
# include 5 and 8
puts "6th to 8th chars: [string range $str 5 8]"

newline

puts "var str2 is \"$str2\""
puts "Compare with str: [string compare $str $str2]"

newline

set hi [string first "h" $str]
puts "str from h: [string range $str $hi [string length $str]]"

newline

set fa [string first "a" $str2]
set la [string last "a" $str2]
puts "first a index in str2: $fa, while last is : $la"

newline

set fs "abc def ghi"
set i [string wordend $fs 2]
puts "$i" ;# should be 3

newline

set upper "THIS IS A STRING IN UPPER CASE LETTERS"
set lower "this is a string in lower case letters"
set trailer "This string has trailing dots ...."
set leader "....This string has leading dots"
set both  "((this string is nested in parens )))"

puts "tolower converts this: $upper"
puts "              to this: [string tolower $upper]\n"
puts "toupper converts this: $lower"
puts "              to this: [string toupper $lower]\n"
puts "trimright converts this: $trailer"
puts "                to this: [string trimright $trailer .]\n"
puts "trimleft converts this: $leader"
puts "               to this: [string trimleft $leader .]\n"
puts "trim converts this: $both"
puts "           to this: [string trim $both "() "]\n"

newline

# format print
puts "[format "%10s:%-5s" right 5]"
puts "[format "%10s:%5.2f" flaot 2.735]" ;# 2.73 not 2.74
