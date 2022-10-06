import std.stdio;
import std.getopt;

int main(string[] args) {
	int repeatTime;
	getopt(args, "time|t", &repeatTime);

	while (repeatTime --> 0) {
		foreach (i, s; args) {
			writefln("args[%d]: %s", i, s);
		}
	}

	return 0;
}
