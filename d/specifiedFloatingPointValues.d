import std.stdio;

void main() {
    writeln("Type                    : ", float.stringof);
    writeln("Precision               : ", float.dig);
    writeln("Minimum normalized value: ", float.min_normal);
    writeln("Minimum value           : ", -float.max);
    writeln("Maximum value           : ", float.max);
    writeln();

    writeln("Type                    : ", double.stringof);
    writeln("Precision               : ", double.dig);
    writeln("Minimum normalized value: ", double.min_normal);
    writeln("Minimum value           : ", -double.max);
    writeln("Maximum value           : ", double.max);
    writeln();

    writeln("Type                    : ", real.stringof);
    writeln("Precision               : ", real.dig);
    writeln("Minimum normalized value: ", real.min_normal);
    writeln("Minimum value           : ", -real.max);
    writeln("Maximum value           : ", real.max);
}
