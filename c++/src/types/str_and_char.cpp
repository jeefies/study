/* It shows the way to convert str into char[] or char[] into string
 * Also shows how to check the platform to decide the .h file to include
 * This way is also useful in functions
 */

#include<iostream>

#ifdef _WIN32
	#include<windows.h>
#else
	#include<unistd.h>
#endif

using namespace std;

#define TIME 3

int fuck(string fucker, string person, int time);
int ssleep(int sec);

int main() {
	cout << "Who are you?" <<  endl;
	char char_fucker[20];
    //  The best way to get the input(must be a char sequence)
	cin.getline(char_fucker, 20);
    // Check if the input is empty or foolish
	if (char_fucker[0] == '\0' or char_fucker[0] == ' ') {
		cout << "Please Enter Your Name!" <<  endl;
		return 1;
	}
	string fucker = char_fucker;
	cout << "Hello " << fucker << endl;

	cout << "Who do you want to FUCK!!!!" <<  endl;
	char c_person[20];
	cin.getline(c_person, 20);
	if (c_person[0] == '\0' or c_person[0] == ' ') {
		cout << "Please Enter Who do you want to FUCK!!!" << endl;
		return 1;
	}
	string person = c_person;
	cout << "FUCKING..." << endl;
	return fuck(fucker, person, TIME);
}

int fuck(string fucker, string person, int time) {
	cout << "That Time, you and your lover " << person << " walked into a dark room together." <<  endl;
	ssleep(time);
	cout << "Why is it so dark ? " << person << " asked you carefully." << endl;
	ssleep(time);
	cout << "You, " << fucker << ", notice that your lover " << person << " was scared." << endl;
	ssleep(time);
	cout << "You thought, \"" << "I just want to fuck you, uh!" << endl;
	ssleep(time);
	cout << "You slowly got close to your lover." << endl;
	ssleep(time);
	cout << "And suddenly PUSH your lover down and took all of you two's clothes." << endl;
	ssleep(time);
	cout << "You kept panting for physical weakness, your lover was doing it, too!" << endl;
	ssleep(time);
	cout << fucker << ", you the Bad Fucker! I Love Your Large DICK!" << endl;
	ssleep(time);
	cout << person << ", I love your Large Breast Too!" << endl;
	ssleep(time * 5);
	cout << "Not long. They had a \"smart\" child." << endl;
	cout << "And they started a HAPPY life,";
	ssleep(time);
	cout << " then." << endl;
	return 0;
}

int ssleep(int sec) {
	#ifdef _WIN32
		Sleep(sec * 1000);
	#else
		sleep(sec);
	#endif
	return 0;
}
