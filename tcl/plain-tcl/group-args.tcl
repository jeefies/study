# Grouping arguments with []

set x abc
puts "now x is $x"

set x [set y cde]
puts -nonewline {but after set x [set y cde], x now is:}
puts $x

set x {[set z efg]}
puts -nonewline {and now we use braces like "set x {[set z efg]}", x turn to:}
puts $x

# newline
puts ""

set x "[set a {This is a string within braces within quotes}]"
puts "a group in \"\" can be affective!"
puts {This is what we do: set x "[set a {This is a string within braces within quotes}]"}
puts "And now, x is $x, a is $a"
puts "they are the same"

# newline
puts ""

set b "\[set y {This is a string within braces within quotes}]"
# Note the \ escapes the bracket, and must be doubled to be a
# literal character in double quotes
puts "Note the \\ escapes the bracket:\nb is: $b"
puts "y is: $y"
puts "an old value right!"
