package require Tk

wm title . "Static text and variables"
wm geometry . "300x300"

frame .m -bg white
pack .m -fill both -expand 1

set btn "Click me"
button .m.btn -textvar ::btn -command changeCtt
bind .m.btn "<Return>" changeCtt

set lbt   "Init Val"
label .m.lb -textvar ::lbt -bg white -borderwidth 2 -relief groove
label .m.lb2 -text $lbt -bg white -borderwidth 2 -relief groove

grid .m.lb -column 0 -row 1 -sticky nsew -pady 3 -padx "0 2"
grid .m.lb2 -column 1 -row 1 -sticky nsew -padx "2 0" -pady 3
grid .m.btn -column 0 -row 2 -columnspan 2 -sticky n 

grid columnconfigure .m 0 -weight 1
grid columnconfigure .m 1 -weight 1

checkbutton .m.ck -text "Change Back" -variable changeback -onvalue 1 	-offvalue 0 -bg white
grid .m.ck -column 0 -row 3 -sticky w -padx "5 0"

proc changeCtt {} {
	set ::lbt "Changed Val"
	set ::btn "With me ok!"
	.m.lb2 configure -text "I changed TOO"

	after 1000 {
		set ::btn "Click me"
		if {$::changeback == 1} {
			set ::lbt "Init val"
			.m.lb2 configure -text "Init val2"
		}
	}
}
