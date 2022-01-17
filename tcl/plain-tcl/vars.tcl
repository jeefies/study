#The assignment command in Tcl is set. 

# set varName ?value?
set var 1
puts $var

# modify the variable
set var "akjhsfd"
puts  $var

# If varName has the form varName(index) , it is a member of an associative array. 
set arr(1) "abc"
# for more array use see array.tcl

puts "" ;# for a new line

# official examples
set X "This is a string"

set Y 1.24

puts $X
puts $Y

puts "..............................."

set label "The value in Y is: "
puts "$label $Y"
