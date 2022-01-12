proc sum {arg1 arg2} {
    set x [expr {$arg1 + $arg2}];
    return $x
}

puts " The sum of 2 + 3 is: [sum 2 3]\n\n"

proc for {a b c} {
    puts "The for command has been replaced by a puts";
    puts "The arguments were: $a\n$b\n$c\n"
}

for {set i 1} {$i < 10} {incr i}

proc say {sth {end "\n"}} {
	puts -nonewline "$sth$end"
	return 0
}

say "Hello" " world"
say ""

proc many { a {b 0} args }  {
	puts $args
}

many 0 0 A B C

# after seeing upvar document online, I still can not fully understand it

proc SetPositive {variable value } {
    upvar $variable myvar
    if {$value < 0} {
        set myvar [expr {-$value}]
    } else {
        set myvar $value
    }
    return $myvar
}

SetPositive x 5
SetPositive y -5

puts "X : $x    Y: $y\n"

proc double { x } {
	set x [ expr $x * 2 ]
	return $x
}

set x 1
set x_r [double $x]
puts "x is still $x, result is $x_r"

proc double2 { x } {
	# like global x in python, but we should give it a new name
	# notice the name bind here should appear outside!
	upvar x ix
	# `upvar $x ix` is not ok
	set ix [ expr $ix * 2 ]
	return $ix
}

set x 1
set x_r [double2 $x]
puts "x changed to $x, result is $x_r"

proc one {y} {
    upvar $y iz                      ;# This ties the calling value to variable z
	puts "y $y, iz $iz"
	incr iz 2
	puts "y $y, iz $iz"
    puts "one: Z: $iz"               ;# Output that value, to check it is 5
	puts "y $y, iz $iz"
}

set z 1
one z
puts "z is changed to $y"
