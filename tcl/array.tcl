proc addname {first last} {
	global name

	incr name(ID)
	set id $name(ID)

	set name($id,first) $first
	set name($id,last)  $last
}

proc printnames {} {
	global name
	set length $name(ID)
	for {set i 1} {$i <= $length} {incr i} {
		puts "ID: $i"
		puts "Name: $name($i,first) $name($i,last)"
	}
}

proc printnames_byFN {} {
	# sort it by first name
	global name
	set length $name(ID)
	# also it's wrong when there's same first name!
	for {set i 1} {$i <= $length} {incr i} {
		lappend tmp $name($i,first) $name($i,last)
	}
	array set tmp2 $tmp
	set names [array names tmp2]
	foreach n [lsort $names] {
		puts "name: $n $tmp2($n)"
	}
}

proc printnames_byLN {} {
	# sort it by last name
	global name
	set length $name(ID)
	# it's not ok if there's same last name!
	for {set i 1} {$i <= $length} {incr i} {
		set tmp($name($i,last)) $name($i,first)
	}

	foreach n [lsort [array names tmp]] {
		puts "name: $tmp($n) $n"
	}
}

proc printname {id} {
	global name
	if {$id > $name(ID)} {
		puts "Error ID"
	} else {
		puts "First name: $name($id,first)"
		puts "Last  name: $name($id,last)"
	}
}

global name
set name(ID) 0

addname Jeefy F
addname Shihan Xue
addname Guo Chen
addname Yongchuan Fu

printnames

printname 2

puts ""
printnames_byFN
puts ""
printnames_byLN
