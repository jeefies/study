set A "print out"
set A_pre "With pre:"

puts "With $ pre: $A"
puts "With \\$ pre: \$A"

# new line
puts ""

puts "let's use braces to print out:"
puts "$A_pre $A"
puts {$A_pre $A}
puts "See, braces would not convert the vars!"
puts "But how if we use \"\" in braces?"
puts {"Some here $A_pre" $A}
# "" would also be printed out!

# newline
puts ""

puts "Notice that the usage of  `\\` is the same as Python or C"
puts "'\\n' still means a new line\nlike this"

puts "and '\\t' also has no change:"
puts "a\tb\tc"
puts "12\t34\t56"

# if line ends with \, tcl might add a ` ` automatically
puts "Sometimes you can see a single line\
written in double line"

# new line
puts ""

puts {There are no substitutions done within braces \n \r \x0a \f \v}
puts {But, the escaped newline at the end of a\
string is still evaluated as a space}
