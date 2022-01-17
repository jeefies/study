set name(first) "Mary"
set name(last) "Honey"

set notarr 0

puts "notarr is arr? [array exists notarr]"
puts "name has names [array names name]"
puts "and size of name is [array size name]"
puts "so the content of name is :[array get name]"

set li [list a b c d e f]
array set arrli $li
parray arrli

unset arrli
puts "arrli should be none now: [array get arrli] (nothing here)"

array unset name "fi*"
puts {after calling unset name fi*}
puts "name should remain just last"
parray name
