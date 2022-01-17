#
# Write a Tcl script to get a platform-independent program:
#
# Create a unique (mostly) file name for a Tcl program
set TMPDIR "/tmp"
if { [info exists ::env(TMP)] } {
    set TMPDIR $::env(TMP)
}
set tempFileName "$TMPDIR/invert_[pid].tcl"

# Open the output file, and
# write the program to it

set outfl [open $tempFileName w]

puts $outfl {
    set len [gets stdin line]
    if {$len < 5} {exit -1}

    for {set i [expr {$len-1}]} {$i >= 0} {incr i -1} {
        append l2 [string range $line $i $i]
    }
    puts $l2
    exit 0
}

# Flush and close the file
flush $outfl
close $outfl

#
# Run the new Tcl script:
#
# Open a pipe to the program (for both reading and writing: r+)
#
set io [open "|[info nameofexecutable] $tempFileName" r+]

#
# send a string to the new program
#     *MUST FLUSH*
puts $io "This will come back backwards."
flush $io

# Get the reply, and display it.
set len [gets $io line]

puts  "To reverse: 'This will come back backwards.'"
puts "Reversed is: $line"
puts "The line is $len characters long"

# Run the program with input defined in an exec call

set invert [exec [info nameofexecutable] $tempFileName << \
       "ABLE WAS I ERE I SAW ELBA"]

# display the results
puts "The inversion of 'ABLE WAS I ERE I SAW ELBA' is \n $invert"

# Clean up
file delete $tempFileName

