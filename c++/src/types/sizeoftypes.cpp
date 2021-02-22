#include<iostream>
#include<limits>
using namespace std;
// import io
// from io import *
#define ends '\t'
/*
 * Bool
 * Char
 * Int
 * Short
 * Long
 * Long Long
 * Unsigned
 * Unsigned Int
 * Unsigned Long
 * Unsigned Char
 * Unsigned Long Long
 * Double
 * Long Double
 * float
 * */
int main() {
	cout << "type: \t\t" << "-----------------------------------" << endl;
	// Bool boolean	
	cout << "size of bool:" << sizeof(bool) << ends;
	cout << "max:" << (numeric_limits<bool>::max)() << ends;
	cout << "min:" << (numeric_limits<bool>::min)() << endl;
	
	// Char
	cout << "size of char:" << sizeof(char) << ends;
	cout << "max:" << (numeric_limits<char>::max)() << ends;
	cout << "min:" << (numeric_limits<char>::min)() << endl;
	
	// Signed Char
	cout << "size of signed char:" << sizeof(signed char) << ends;
	cout << "max:" << (numeric_limits<signed char>::max)() << ends;
	cout << "min:" << (numeric_limits<signed char>::min)() << endl;

	// Int
	cout << "size of int:" << sizeof(int) << ends;
	cout << "max:" << (numeric_limits<int>::max)() << ends;
	cout << "min:" << (numeric_limits<int>::min)() << endl;
	
	// Short
	cout << "size of short:" << sizeof(short) << ends;
	cout << "max:" << (numeric_limits<short>::max)() << ends;
	cout << "min:" << (numeric_limits<short>::min)() << endl;
	
	// Long
	cout << "size of long:" << sizeof(long) << ends;
	cout << "max:" << (numeric_limits<long>::max)() << ends;
	cout << "min:" << (numeric_limits<long>::min)() << endl;

	// Long Long
	cout << "size of long long:" << sizeof(long long) << ends;
	cout << "max:" << (numeric_limits<long long>::max)() << ends;
	cout << "min:" << (numeric_limits<long long>::min)() << endl;

	// Unsigned
	cout << "size of unsigned:" << sizeof(unsigned) << ends;
	cout << "max:" << (numeric_limits<unsigned>::max)() << ends;
	cout << "min:" << (numeric_limits<unsigned>::min)() << endl;
	
    // Signed Int == Int
	cout << "size of signed int:" << sizeof(signed int) << ends;
	cout << "max:" << (numeric_limits<signed int>::max)() << ends;
	cout << "min:" << (numeric_limits<signed int>::min)() << endl;
    
	// Unsigned Int == Unsigned
	cout << "size of unsigned int:" << sizeof(unsigned int) << ends;
	cout << "max:" << (numeric_limits<unsigned int>::max)() << ends;
	cout << "min:" << (numeric_limits<unsigned int>::min)() << endl;

	// Unsigned Long
	cout << "size of unsigned long:" << sizeof(unsigned long) << ends;
	cout << "max:" << (numeric_limits<unsigned long>::max)() << ends;
	cout << "min:" << (numeric_limits<unsigned long>::min)() << endl;
	
	// Unsigned Char
	cout << "size of unsigned char:" << sizeof(unsigned char) << ends;
	cout << "max:" << (numeric_limits<unsigned char>::max)() << ends;
	cout << "min:" << (numeric_limits<unsigned char>::min)() << endl;

	// Unsigned Long Long
	cout << "size of unsigned long long:" << sizeof(unsigned long long) << ends;
	cout << "max:" << (numeric_limits<unsigned long long>::max)() << ends;
	cout << "min:" << (numeric_limits<unsigned long long>::min)() << endl;
	
	// Double
	cout << "size of double:" << sizeof(double) << ends;
	cout << "max:" << (numeric_limits<double>::max)() << ends;
	cout << "min:" << (numeric_limits<double>::min)() << endl;

	// Long Double
	cout << "size of long double:" << sizeof(long double) << ends;
	cout << "max:" << (numeric_limits<long double>::max)() << ends;
	cout << "min:" << (numeric_limits<long double>::min)() << endl;
	
	// Float
	cout << "size of float:" << sizeof(float) << ends;
	cout << "max:" << (numeric_limits<float>::max)() << ends;
	cout << "min:" << (numeric_limits<float>::min)() << endl;
}
