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
	{Raspberry Pi OS (32-bit)} {A port of DEBIAN Buster with the Raspberry Pi Desktop (Recommened)}
	https://mirrors.tuna.tsinghua.edu.cn/raspberry-pi-os-images/raspios_armhf/images/raspios_armhf-2021-05-28/2021-05-07-raspios-buster-armhf.zip
	{Raspberry Pi OS (64-bit)} {The same with above, but for 64-bits}
	https://mirrors.tuna.tsinghua.edu.cn/raspberry-pi-os-images/raspios_arm64/images/raspios_arm64-2021-05-28/2021-05-07-raspios-buster-arm64.zip
	{RaspiOS (lite 32-bit)} {A tiny version of Raspios, without any desktop environment}
	https://mirrors.tuna.tsinghua.edu.cn/raspberry-pi-os-images/raspios_lite_armhf/images/raspios_lite_armhf-2021-05-28/2021-05-07-raspios-buster-armhf-lite.zip
	{RaspiOS (lite 64-bit)} {The same as above, buf for 64-bit}
	https://mirrors.tuna.tsinghua.edu.cn/raspberry-pi-os-images/raspios_lite_arm64/images/raspios_lite_arm64-2021-05-28/2021-05-07-raspios-buster-arm64-lite.zip
	{Chromium OS} {A Chromiun version from FydeOS in github.com}
	https://github.com/FydeOS/chromium_os-raspberry_pi/releases/download/r92/chromiumos_image_r92r1-rpi4b.img.xz
	{Manjaro Mate} {Manjaro linux system with mate desktop}
	https://mirrors.tuna.tsinghua.edu.cn/osdn/storage/g/m/ma/manjaro-arm/rpi4/mate/20.12.1/Manjaro-ARM-mate-rpi4-20.12.1.img.xz
	{Fedora Lite} {Fedora linux system without desktop environment installed}
	https://mirrors.tuna.tsinghua.edu.cn/fedora-altarch/releases/34/Spins/aarch64/images/Fedora-Minimal-34-1.2.aarch64.raw.xz
	{OpenEular UKUI} {A Chinese system created by huawei, with UKUI desktop}
	https://isrc.iscas.ac.cn/eulixos/repo/others/openeuler-raspberrypi/images/openEuler-20.03-LTS-SP1-UKUI-raspi-aarch64-alpha2.img.xz
	{OpenEular DDE} {The same as above, but with DDE desktop environment}
	https://isrc.iscas.ac.cn/eulixos/repo/others/openeuler-raspberrypi/images/openEuler-20.03-LTS-SP1-DDE-raspi-aarch64-alpha2.img.xz
	{擦除} {格式化SD卡为FAT32格式}
	{使用自定义镜像} {使用下载的系统文件镜像文件烧录}
}

proc chooseOS {} {
	set x [winfo x .]
	set y [winfo y .]
	showList "操作系统" $::systemContent [expr $x + 40] [expr $y + 10]
}
