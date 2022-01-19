# catch is like try in python
# error is like throw in python
#
proc errorproc {{vars 0}} {
	if {$vars == 0} {
		error "Hey girl, do you like me?"
	} else {
		error "Okk, Error Threw" "Here's the message" $vars
	}
}

proc perror {} {
	puts "Error Code: $::errorCode"
	puts "Error Info:\n$::errorInfo"
	puts "" ;# a newline
}

catch errorproc
# ok, now we catch the error, but what's it ?
perror

catch  {errorproc 1}
perror

# We also can return with error info, we also need to "catch it"
# -code can be one of [ok error return break continue]
proc ereturn {} {
	return -code error -errorinfo "Infomation here" -errorcode 2 "return value"
}

catch ereturn
perror

puts "All Error Caught!"

# so try except in tcl is like
if {[catch {
	set x [expr {0/0}]
}]} {
	puts "Exception place !"
	perror
}
