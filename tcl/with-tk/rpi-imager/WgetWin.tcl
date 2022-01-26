lappend auto_path [file normal "./tcurl"]
package require tcurl

puts "with tcurl ok"

package require Tk
set DEV 0

proc getUrlPBar {parent url} {
	array set heads [::tc::urlAget $url]
	if {[catch {set total $heads(content-length)}]} {
		parray heads
		exit 1
	}

	puts "head ok"

	set pbar [ttk::progressbar $parent.pbar -max $total -length 200]
	update

	label $parent.purl -text "donwloading [file tail $url]" -bg white
	grid $parent.purl -column 0 -row 0 -columnspan 4

	label $parent.plabel -text "to [::tc::getfn]" -bg white
	grid $parent.plabel -column 0 -row 1

	grid $parent.pbar -column 1 -row 1 -columnspan 3

	set last 0
	while {[::tc::urlAfinish] == $::tc::NOT_FINISH} {
		set now [::tc::urlAsize]
		if {$now == 0} {
			break
		}
		$parent.pbar step [expr {$now - $last}]
		update
		set last $now

		after 50
	}

	tk_messageBox -icon info -message "Download Image file finished" -type ok -parent $parent
}

if {$::DEV == 1} {
	wm title . "Test"
	frame .main -bg white
	pack .main -fill both -expand 1
	update

	getUrlPBar .main "https://mirrors.tuna.tsinghua.edu.cn/raspberry-pi-os-images/imager/imager_1.5_amd64.AppImage"
	puts "ok"
}
