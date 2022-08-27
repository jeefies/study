import std.stdio;

void main() {
	float lowAccuracy = 0.0;
	int counter = 0;
	while (++counter <= 1000) {
		lowAccuracy += 0.001;
	}

	writeln("lowAccuracy is updated to ", lowAccuracy);

	double highAccuracy = 0.0;
	counter = 0;
	while(++counter <= 1000) {
		highAccuracy += 0.001;
	}

	writeln("highAccuracy is updated to ", highAccuracy);
}
