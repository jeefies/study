set pkg_path [file join / home pi study tcl plain-tcl pkgex ]
lappend auto_path $pkg_path

package require jfu

jfu::hello
jfu::help
jfu::hello
