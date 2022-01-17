puts "This is how many commands have been executed: [info cmdcount]"
puts "Now  *THIS* many commands have been executed: [info cmdcount]"

puts "\nThis interpreter is revision level: [info tclversion]"
puts "This interpreter is at patch level: [info patchlevel]"

puts "The process id for this program is [pid]"

proc factorial {val} {
    puts "Current level: [info level] - val: $val"
    set lvl [info level]
    if {$lvl == $val} {
        return $val
    }
    return [expr {($val-$lvl) * [factorial $val]}]
}

set count1 [info cmdcount]
set fact [factorial 3]
set count2 [info cmdcount]
puts "The factorial of 3 is $fact"
puts "Before calling the factorial proc, $count1 commands had been executed"
puts "After calling the factorial proc, $count2 commands had been executed"
puts "It took [expr $count2-$count1] commands to calculate this factorial"
puts ""

#
# Use [info script] to determine where the other files of interest
# reside
#
# set sysdir [file dirname [info script]]
# source [file join $sysdir "utils.tcl"]


# for proc use
proc demo {argument1 {default "DefaultValue"} } {
    puts "This is a demo proc.  It is being called with $argument1 and $default"
    #
    # We can use [info level] to find out if a value was given for
    # the optional argument "default" ...
    #
	# Returns the stack level at which the compiler is currently evaluating code. 0 is the top level, 1 is a proc called from top, 2 is a proc called from a proc, etc.
	# If number is a positive value, info level returns a the name and arguments of the proc at that level on the stack. Number is that same value that info level would return if it were called in the proc being referenced.
	# If number number is a negative value, it refers to the current level plus number. Thus, info level returns a the name and arguments of the proc at that level on the stack.
    puts "Actual call: [info level [info level]]"
}

puts "The args for demo are: [info args demo]\n"
puts "The body for demo is:  [info body demo]\n"

set arglist [info args demo]

foreach arg $arglist {
	# Returns 1 if the argument arg in procedure procName has a default, and sets varName to the default. Otherwise, returns 0. 
    if {[info default demo $arg defaultval]} {
        puts "$arg has a default value of $defaultval"
    } else {
        puts "$arg has no default"
    }
}

demo {...?}
