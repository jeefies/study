import std.stdio;

void main(){
	switch(4) {
		case 1:
			writeln("1");
			goto case; // we need to call it directly
		case 2:
			writeln("Not here!");
			break;
		default:
			writeln("Why?");
			goto case 1; /* We can goto specific case */
			break;
	}
}
