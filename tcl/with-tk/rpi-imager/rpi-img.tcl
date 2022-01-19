package require Tk

source FormList.tcl

wm title . "树梅派镜像烧录 自制"
wm geometry . "680x420"
wm resizable . 0 0
image create photo rpiIcon -file "imager.png"
wm iconphoto . rpiIcon

# Get the color from rpi-image
set RED "#be1b48"

# Frame up and down
# Up use pack
# Down use grid, with three labels and three buttons
#

frame .up -bg white
frame .down -bg $RED

# set two frame to the same size, up and down
grid rowconfigure . 0 -weight 1 -uniform a
grid rowconfigure . 1 -weight 1 -uniform a
# make sure them takes all place
grid columnconfigure . 0 -weight 1

grid .up -row 0 -sticky nsew
grid .down -row 1 -sticky nsew

# Up Frame with two things, one is the icon, and another one is the text "Raspberry Pi"

set RPI "Raspberry Pi"
# get it from package rpi-imager
# Use `apt download rpi-imager` to download it
# It's a PNG format image, but Tk can use it

font create IconFont -size 25 -weight bold
font create BoldFont -weight bold
label .up.img -image rpiIcon -bg white -font IconFont
label .up.text -text $RPI -bg white -font IconFont
pack .up.img -expand y
pack .up.text -side bottom -pady "0 5"


# Down frame with two labels and three buttom
# Use grid for it
set Wwi 19
set Whe 2
label .down.lsys -text "操作系统"  -bg $RED -fg white -font BoldFont
label .down.lsdc -text "SD卡" -bg $RED -fg white -font BoldFont
# button .down.bsys 	-text "选择操作系统" 	-bg white -fg $RED -activeforeground $RED\
# 	-width $Wwi -height $Whe -borderwidth 0
# button .down.bsdc 	-text "选择SD卡"	-bg white -fg $RED -activeforeground $RED\
# 	-width $Wwi -height $Whe -borderwidth 0
# button .down.bstart -text "烧录" 				-bg white -fg $RED -activeforeground $RED\
# 	-width $Wwi -height $Whe -borderwidth 0 -state disable
# I used to want to use Button, but after coding, I found Label is much more suitable
set LW 20
set LH 2
label .down.bsys -text "选择操作系统" 	-bg white -fg $RED -width $LW -height $LH
label .down.bsdc -text "选择SD卡" 		-bg white -fg $RED -width $LW -height $LH
label .down.bstart -text "烧录" 		-bg white -fg $RED -width $LW -height $LH
grid .down.lsys -column 0 -row 0
grid .down.lsdc -column 1 -row 0

grid .down.bsys -column 0 -row 1 -sticky n
grid .down.bsdc -column 1 -row 1 -sticky n
grid .down.bstart -column 2 -row 1 -sticky n

grid columnconfigure .down 0 -weight 1 -pad 3
grid columnconfigure .down 1 -weight 1 -pad 3
grid columnconfigure .down 2 -weight 1 -pad 3
grid rowconfigure .down 0 -pad 30
grid rowconfigure .down 1 -weight 1 -pad 5

# Bind !
bind .down.bsys "<Button-1>" {chooseOS}


set systemContent {
	{Raspberry Pi OS (32-bit)} {A port of DEBIAN Bullseye with the Raspberry Pi Desktop (Recommened)}
	{Raspberry Pi OS (other)} {Other Raspberry Pi OS based images}
	{Other general purpose OS} {Other general purpose Operating Systems}
	{Media player - Kodi OS} {Kodi based Media player Operating Systems}
	{Emulation and game OS} {Emalators for running retro-computing platforms}
	{Other specific purpose OS} {Thin clients, digit signage and 3D printers OS}
	{Other language-specific OS} {Operating systems specifically tailored for particular langauges}
	{Misc utility images} {Bootloader EEPROM configuration, etc.}
	{擦除} {格式化SD卡为FAT32格式}
	{使用自定义镜像} {使用下载的系统文件镜像文件烧录}
}

proc chooseOS {} {
	set x [winfo x .]
	set y [winfo y .]
	showList "操作系统" $::systemContent [expr $x + 40] [expr $y + 10]
}
