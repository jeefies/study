# dict is like array in tcl
# Tcl dictionaries are therefore much more like Tcl lists
# except that they represent a mapping from keys to values,
# rather than an ordered sequence

proc addname {dbVar first last} {
	upvar 1 $dbVar db

	dict incr db ID
	set id [dict get $db ID]

	dict set db $id first $first
	dict set db $id last  $last
}

proc report {db} {
	# because we don't need to change it, so we just pass the value in
	
	dict for {id name} $db {
		if {$id eq "ID"} {continue}
		set tmp([dict get $name last]) $id
	}

	foreach n [lsort [array names tmp]] {
		set id $tmp($n)
		puts "ID: $id"
		puts "Name: [dict get $db $id first] $n"
	}
}

dict set sch_name ID 0

addname sch_name Shihan Xue
addname sch_name Jeefy Fu
addname sch_name YongChuan Shabi

report $sch_name
