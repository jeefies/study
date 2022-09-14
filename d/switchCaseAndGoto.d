import std.stdio;

void main() {
	int val = 5;

    switch (val) {
    case 5:
        writeln("five");
        goto case;    // continues to the next case

    case 4:
        writeln("four");
        break;

    default:
        writeln("unknown");
        break;
    }
	
    foreach (value; [ 1, 2, 3, 10, 20 ]) {
        writefln("--- value: %s ---", value);

        switch (value) {
        case 1:
            writeln("case 1");
            goto case 10;

        case 2:
            writeln("case 2");
            goto case;

        case 3:
            writeln("case 3");
            goto default;

        case 10:
            writeln("case 10");
            break;

        default:
            writeln("default");
            break;
        }
    }
}
