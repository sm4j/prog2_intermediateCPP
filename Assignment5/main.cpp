/*

Jordan Small
Assignment 5
4 APR 2024

This program desmonstrates the use of the Rational class.
Below is a series of debugging to ensure functionality of
all member functions and usage.

*/

// Include necessary libraries, as well as header file in the directory
#include <iostream>
#include "rationalJS.h"
using namespace std;

int main() {
	
	using RATIONAL_SMALL::Rational;

	// Instantiate Rational object using default constructor
	Rational one;

	// Test overloaded input and output
	cin >> one;
	cout << one << endl;
	
	// Instantiate rational objects using 2 int constructor
	Rational half(1, 2);
	Rational third(1, 3);

	// Test overloaded equality operator
	if (half > third) cout << endl << "Correct!" << endl << endl;
	else cout << endl << "Incorrect!" << endl << endl;
	
	// Test overloaded binary and unary algebraic operators
	Rational add = half + third;
	Rational sub = half - third;
	Rational prod = half * third;
	Rational div = half / third;
	Rational neg = -half;

	// Output results of test
	cout << "1/2 + 1/3 = " << add << endl;
	cout << "1/2 - 1/3 = " << sub << endl;
	cout << "1/2 * 1/3 = " << prod << endl;
	cout << "1/2 / 1/3 = " << div << endl << endl;
	cout << "-(1/2) = " << neg << endl << endl;

	// Test overloaded equality operators and output results
	cout << "1/2 > 1/3 ? ";
	if (half > third) cout << "Yes" << endl;
	else cout << "No" << endl;

	cout << "1/2 < 1/3 ? ";
	if (half < third) cout << "Yes" << endl;
	else cout << "No" << endl;

	cout << "1/2 == 1/3 ? ";
	if (half == third) cout << "Yes" << endl;
	else cout << "No" << endl;

	cout << "1/2 != 1/3 ? ";
	if (half != third) cout << "Yes" << endl << endl;
	else cout << "No" << endl << endl;

	// Test simplify helper functions
	// Test case 1: d%n == 0
	Rational four(5, 10);
	cout << four << endl;

	// Test case 2: n > 0, d > 0
	Rational five(-3, -5);
	cout << five << endl;

	// Test case 3: combination of test case 1 and 2
	Rational six(-2, -4);
	cout << six << endl;

	return 0;

}