puts "Hello world!" ;# notice the comment after line should start with `;`
# but this needn't
puts {Hello world - In Braces}

puts "Two line can puts together, with new line"; puts {See source !}

puts "But you can avoid a new line by using `-nonewline` option:"
puts -nonewline "like this "; puts "! another puts"

puts "You can also have a ; inside the string"
