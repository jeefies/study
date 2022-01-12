# if examples

set x 1

if { $x == 2 } {
	puts "x is equal to two"
} else {
	puts "x is not 2 but $x"
}

set a(0) 1
set a(1) 2

if { $a(0) == 2 } {
	puts "1"
} elseif {$a(1) == 2} {
	puts "a1 is 2"
}

# switch
# it's a good idea to use the switch command when you want to match a variable against several possible values, and don't want to do a long series of if... elseif ... elseif statements. 
set y "abc"
switch $y {
	"ab" {
		set y1 "cde"
		puts "y is $y, and y1 should be $y1"
	}
	ABC {
		set y1 "ABC"
		puts "Not sensitive for case !"
	}
	abc {
		set y1 "abc"
		puts "ok to use str without \" ! $y1"
	}
	default {
		puts "no match case"
	}
}

# while loop
set mn 5
while { $x < $mn } {
	incr x 2
	incr mn 1
	puts "now x mn are $x $mn"
}

set x 1
while { 1 == 1 } {
	incr x
	if { $x == 5 } {
		break
	}
	if { $x == 3 } {
		continue
	}
	puts "x = $x"
}

# for loop
# equal to:
# for (int i = 0; i < 10; i++) { ... }
for { set i 0 } { $i < 10 } { incr i } {
	puts "Loop loop loop $i"
}
