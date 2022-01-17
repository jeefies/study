package provide jfu 1.0
package require Tcl 8.6

namespace eval ::jfu {
	# Export namespace procs out
	namespace export hello help

	# Set up a few vars to use in the namespace
	variable hasHelped 0
}

proc ::jfu::hello {} {
	# declare the use of the var
	variable hasHelped

	puts "Hello, I'm Jeefy Fu"
	if {$hasHelped == 1} {
		puts "You have helped me"
	} else {
		puts "I need some help"
	}
}

proc ::jfu::help {} {
	variable hasHelped

	if {$hasHelped == 1} {
		puts "You have already helped me!"
	} else {
		puts "Thanks for your help"
		set hasHelped 1
	}
}
