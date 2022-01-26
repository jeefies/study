package require Tk

source WgetWin.tcl

set DEV 0

font create Name -size 12 -weight bold
font create Detail -size 11
font create Title -size 15 -weight bold
set MUNSELL "#f2f3f4"

proc showList {title ctx {x 200} {y 200}} {
	# upvar $cListVar ctx
	# puts $ctx
	set w .top
	catch {destroy $w}
	toplevel $w
	# We don't need to use title because we hide the decorations around the window
	# But we can use it to set the Icon's Name shown on the bar
	wm title $w $title
	wm overrideredirect $w 1
	wm geometry $w "600x400+$x+$y"
	update

	# Fisrt for top close frame
	set top $w.top
	pack [frame $top -bg $::MUNSELL] -side top -fill x
	label $top.title -text " $title" -bg $::MUNSELL -font Title
	label $top.btn -bg $::MUNSELL -border 0 -image [image create bitmap -file "x.xbm"] -cursor hand2
	pack $top.btn -side right
	pack $top.title -side right -expand 1

	bind $top.btn <Button-1> {
		destroy .top
		if {$::DEV == 1} {
			exit 0
		}
	}

	set down $w.down
	pack [frame $down -bg white -border 0] -fill both -expand 1

	set wrapper $down.mainwrapper
	pack [scrollbar $down.scroll -orient vertical -command "$wrapper yview"] -side right -fill y
	pack [canvas $wrapper -bg white -yscrollcommand "$down.scroll set" -bd 0] -expand 1 -fill both

	# For Content Frame
	set main $wrapper.main
	pack [frame $main -bg white -bd 0]
	$wrapper create window 0 0 -window $main -anchor nw

	set size [expr {[llength $ctx] / 3}]

	set index -1
	for {set i 0} {$i < $size} {incr i} {
		packOne $main $i [lindex $ctx [incr index]] [lindex $ctx [incr index]]
		sepLine $main $i
		bindDownload $main $i [lindex $ctx [incr index]]
	}
	packOne $main $i [lindex $ctx [incr index]] [lindex $ctx [incr index]]


	update
	puts [bind $down.scroll]
	$wrapper configure -scrollregion [$wrapper bbox all]
	# This is no use at all !
	# bind all "<MouseWheel>" move
	# bind $down "<MouseWheel>" move
	# bind $main "<MouseWheel>" move
	# bind $wrapper "<MouseWheel>" move
	# 
	set move {
		set delta 10
		set num [expr {$delta}]
		puts "$num"
		.top.down.mainwrapper yview scroll $num units
	}
	bind all "<Button-4>" {
		.top.down.mainwrapper yview scroll -2 units
	}
	bind all "<Button-5>" {
		.top.down.mainwrapper yview scroll 2 units
	}
	
}

proc packOne {parent index name detail} {
	
	set fn $parent.f$index
	frame $fn -bg white -cursor hand2
	pack $fn -side top -fill x

	label $fn.name -text $name -font Name -bg white -anchor w
	label $fn.detail -text $detail -font Detail -bg white -anchor w -justify left -wraplength 575
	pack  $fn.name -side top -fill x -padx "15 0" -expand 1
	pack  $fn.detail -side top -fill x -padx "20 0" -expand 1

	bind $fn "<Enter>" "$fn configure -bg $::MUNSELL;\
		$fn.name configure -bg $::MUNSELL;\
		$fn.detail configure -bg $::MUNSELL"
	bind $fn "<Leave>" "$fn configure -bg white;\
		$fn.name configure -bg white;\
		$fn.detail configure -bg white"
}

proc sepLine {parent index} {
	set n $parent.l$index
	frame $n -bg black -height 2
	pack $n -fill x -padx 10
}

proc bindDownload {parent index url} {
	set n $parent.f$index

	foreach ch [winfo children $n] {
		bind $ch "<Button-1>" "catch {destroy .dltop};
			toplevel .dltop;\
			wm title .dltop Download;\
			getUrlPBar .dltop $url"
	}
}
