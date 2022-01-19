package require Tk

wm title . "Raspberry Pi Imager"
wm geometry . "300x300"

# Frame up and down
# Up use pack
# Down use grid, with three labels and three buttons
#

frame .up -bg white
frame .down -bg red

# set two frame to the same size, up and down
grid rowconfigure . 0 -weight 1
grid rowconfigure . 1 -weight 1
# make sure them takes all place
grid columnconfigure . 0 -weight 1

grid .up -row 0 -sticky nsew
grid .down -row 1 -sticky nsew

# Up Frame with two things, one is the icon, and another one is the text "Raspberry Pi"

set RPI "Raspberry Pi"
# get it from package rpi-imager
# Use `apt download rpi-imager` to download it
# It's a PNG format image, but Tk can use it
image create photo rpiIcon -file "imager.png"

label
