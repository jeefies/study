# The Tcl command for doing math type operations is expr.

# num in tcl format in 0x..... 0.... 0b.. and normal ones
# 0x. for hex, 0. for oct, 0b. for bin

set n9 "9"
set n90 "9.0"

# remember to differ == and eq
# == can convert str to number and then compare
# eq force the value unchanged, and then compare
puts [expr $n9 == $n90] ;# 1 true
puts [expr $n9 eq $n90] ;# 0 false

set var 0
lappend var 1

puts [expr {0 in $var}] ;# 1 true
puts [expr {2 in $var}] ;# 0 false

set x 1
set str "abcdef"
puts [expr { [string length $str] + 2 * $x }] ;# 6 + 2 * 1 = 8

#  Tcl supports the following mathematical functions in expressions:
# abs         acos        asin        atan
# atan2       bool        ceil        cos
# cosh        double      entier      exp
# floor       fmod        hypot       int
# isqrt       log         log10       max
# min         pow         rand        round
# sin         sinh        sqrt        srand
# tan         tanh        wide

set x -1
puts [expr {abs($x)}] ;# 1
puts [expr { double($x) }] ;# -1.0

set a 45 ;# degree
puts [ expr { tanh($a) } ] ;# 1
set pi6 [ expr (3.1415926 / 6.0) ]
puts "pi6 = $pi6"
puts "sin pi6 [ expr {sin($pi6)} ] cos: [ expr cos($pi6) ] tan: [ expr tan($pi6) ]"

set b 3.5
# 向下取整
puts [ expr { floor($b) } ] ;# 3.0
# 向上取整
puts [ expr { ceil($b) } ] ;# 4.0
# fmod取余
puts [ expr { fmod($a, $b) } ] ;# 3.0

# Tcl supports the following functions to convert from one representation of a number to another:
# double int wide entier
# double() converts a number to a floating-point number.
# int() converts a number to an ordinary integer number (by truncating the decimal part).
# wide() converts a number to a so-called wide integer number (these numbers have a larger range).
# entier() coerces a number to an integer of appropriate size to hold it without truncation. This might return the same as int() or wide() or an integer of arbitrary size (in Tcl 8.5 and above).


puts ""
# Working with arrays
set arr(1) 10
set arr(2) 7
set arr(3) 17
set b    2
puts "Sum: [expr {$arr(1)+$arr($b)}]"
parray arr

puts ""

puts "1/2 is [expr {1/2}]"
puts "-1/2 is [expr {-1/2}]"
puts "1/2 is [expr {1./2}]"
puts "1/3 is [expr {1./3}]"
puts "1/3 is [expr {double(1)/3}]"
