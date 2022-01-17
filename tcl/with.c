// compile it with
// gcc % -o %< -ltcl8.6
#include <stdio.h>
#include <tcl.h>

char * lines = 
"set x 1\n"
"puts $x"
;

int main() {
	Tcl_Interp * interp;

	interp = Tcl_CreateInterp();

	int status = Tcl_Eval(interp, lines);
	if (status == TCL_OK) {
		printf("Execute program Successfully!\n");
	}
}
