import std.stdio;
import std.random;

void main() {
	int number = uniform(1, 101);

	int guess;

	writeln("I am thinking a number between 1 and 100");

	do {
		write("Guess my number: ");
		readf(" %s", guess);

		if (guess < number) {
			writeln("I'm bigger than you!");
		} else if (guess > number) {
			writeln("Too large!");
		}
	} while (guess != number);

	writeln("Correct Idiot!");
}
