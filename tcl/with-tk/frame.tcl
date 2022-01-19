# Question:
# I don't know why if there's any widget on a frame
# the background option of the frame would not be performed properly
# Run the program and see what's happening

package require Tk

wm title . "TTK Frame Example"
wm geometry . "400x400"

ttk::style configure Danger.TFrame -background red -borderwith 5

frame .f1 -width 100 -height 100 -relief raised -bg red
place .f1 -x 25 -y 25

ttk::frame .f2 -width 100 -height 100 -relief sunken -style Danger.TFrame
place .f2 -x 150 -y 25

ttk::frame .f3 -width 100 -height 100 -relief solid -style Danger.TFrame
place .f3 -x 25 -y 150

ttk::frame .f4 -width 100 -height 100 -relief ridge -style Danger.TFrame
place .f4 -x 150 -y 150

ttk::frame .f5 -width 100 -height 100 -relief groove -style Danger.TFrame
place .f5 -x 25 -y 275

#label .f1.l -text "Raised"
#pack .f1.l
label .f2.l -text "Sunken"
pack .f2.l
label .f3.l -text "Solid"
pack .f3.l
label .f4.l -text "Ridge"
pack .f4.l
label .f5.l -text "Groove" -bg red
pack .f5.l
