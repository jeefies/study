/*
 * A file to try to convert str into char list
 */

#include<iostream>
using namespace std;

int main() {
    char chars[] = "Some char";
    cout << chars << endl;
    string str = chars;
    cout << str << endl;
    char rchars[10];
    for (int i = 0; i < 9; i++) {
        rchars[i] = char(str[i]);
        // cout << i << str[i] << '\t' << rchars[i] << endl;
    }
    rchars[9] = '\0';
    cout << rchars << endl;
}
