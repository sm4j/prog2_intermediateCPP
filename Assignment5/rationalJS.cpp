/*

Jordan Small
Assignment 5
4 APR 2024

Implementation file rationalJS.cpp - This is the implementation of
the ADT Rational. The interface for the class Rational is in the
header file rationalJS.h.

*/

#include <iostream>
#include <cmath>
#include "rationalJS.h"

using namespace std;

namespace RATIONAL_SMALL {

	// Default constructor
	Rational::Rational() {
		numerator = 0;
		denominator = 1;
	}

	// Constructor with one int value
	Rational::Rational(int num) {
		numerator = num;
		denominator = 1;
	}

	// Constructor with two int values
	Rational::Rational(int num, int den) {
		numerator = num;
		denominator = den;
	}

	// Getters
	int Rational::getNum(const Rational no1) {
		return no1.numerator;
	}

	int Rational::getDen(const Rational no1) {
		return no1.denominator;
	}

	// Input >> overload
	istream& operator >>(istream& in, Rational& no1) {

		char slash;
		char choice;

		// Allow user to choose input method
		cout << "Chose the input method for your rational number: " << endl
			<< "a) X/Y (with slash)" << endl
			<< "b) X/1 (whole number)" << endl
			<< "c) X then Y (X/Y)" << endl;

		cin >> choice;
		choice = toupper(choice);
		cout << endl;

		switch (choice) {

		case 'A':

			// Use do while to check "/" is included and denominator != 0
			do {

				cout << "Enter your rational number (with form numerator/denominator): ";
				in >> no1.numerator >> slash >> no1.denominator;

				if (slash != '/' || no1.denominator == 0) cout << endl << "Invalid input." << endl << endl;

			} while (slash != '/' || no1.denominator == 0);

			break;

		case 'B':

			cout << "Enter your whole number: ";
			in >> no1.numerator;
			no1.denominator = 1;

			break;

		case 'C':

			// Use do while to check denominator != 0
			do {

				cout << "Enter numerator: ";
				in >> no1.numerator;
				cout << "Enter denominator: ";
				in >> no1.denominator;

				if (no1.denominator == 0) cout << endl << "Invalid input." << endl << endl;

			} while (no1.denominator == 0);

			break;

		default: 
			
			cout << "Invalid selection." << endl;
			exit(1);

		}

		return in;

	}

	// Output << overload
	ostream& operator <<(ostream& out, const Rational& no1) {

		out << no1.numerator << "/" << no1.denominator;

		// If numerator = 0, 0/Y = 0
		if (no1.numerator == 0) {
			out << " simplified to: " << no1.numerator;
			return out;
		}

		Rational temp = no1;

		// If both numerator and denominator are negative, simplify to positive
		if (temp.numerator < 0 && temp.denominator < 0) {

			temp.numerator *= -1;
			temp.denominator *= -1;

			out << " simplified to: " << (temp.numerator) << "/" << (temp.denominator);

		}

		// Pass copy of no1 to simplify helper function
		Rational local = simplify(temp);

		// If simplified result is different than original, display simplified rational
		if (temp.numerator != local.numerator && temp.denominator != local.denominator) {
			out << " simplified to: " << local.numerator << "/" << local.denominator;
		}

		// If denominator = 1, X/1 = X
		if (local.denominator == 1) out << " simplified to: " << no1.numerator;

		return out;

	}

	// Overload + operator
	Rational operator +(const Rational no1, const Rational no2) {

		// a/b + c/d = (a*d + b*c) / (b*d)
		Rational add;

		add.numerator = (no1.numerator * no2.denominator + no2.numerator * no1.denominator);
		add.denominator = no1.denominator * no2.denominator;

		return add;

	}

	// Overload - operator (binary)
	Rational operator -(const Rational no1, const Rational no2) {

		// a/b - c/d = (a*d - b*c) / (b*d)
		Rational sub;

		sub.numerator = (no1.numerator * no2.denominator - no2.numerator * no1.denominator);
		sub.denominator = no1.denominator * no2.denominator;

		return sub;

	}

	// Overload * operator
	Rational operator *(const Rational no1, const Rational no2) {

		// (a/b) * (c/d) = (a*c) / (b*d)
		Rational prod;

		prod.numerator = no1.numerator * no2.numerator;
		prod.denominator = no1.denominator * no2.denominator;

		return prod;

	}

	// Overload / operator
	Rational operator /(const Rational no1, const Rational no2) {

		// (a/b) / (c/d) = (a*d) / (c*b)
		Rational div;

		div.numerator = no1.numerator * no2.denominator;
		div.denominator = no2.numerator * no1.denominator;

		return div;

	}

	// Overload - operator (unary)
	Rational operator -(const Rational no1) {

		Rational neg;

		neg.numerator = -(no1.numerator);
		neg.denominator = no1.denominator;

		return neg;

	}

	// Overload > operator
	bool operator >(const Rational no1, const Rational no2) {

		return ((no1.numerator * no2.denominator) > (no2.numerator * no1.denominator));

	}

	// Overload < operator
	bool operator <(const Rational no1, const Rational no2) {

		return ((no1.numerator * no2.denominator) < (no2.numerator * no1.denominator));

	}

	// Overload == operator
	bool operator ==(const Rational no1, const Rational no2) {

		return ((no1.numerator * no2.denominator) == (no2.numerator * no1.denominator));

	}

	// Overload != operator
	bool operator !=(const Rational no1, const Rational no2) {

		return ((no1.numerator * no2.denominator) != (no2.numerator * no1.denominator));

	}

	// Overload >= operator
	bool operator >=(const Rational no1, const Rational no2) {

		return ((no1.numerator * no2.denominator) >= (no2.numerator * no1.denominator));

	}

	// Overload <= operator
	bool operator <=(const Rational no1, const Rational no2) {

		return ((no1.numerator * no2.denominator) <= (no2.numerator * no1.denominator));

	}

	// Simplify helper function
	// Takes a Rational object as a parameter and returns its simplified version
	Rational simplify(const Rational& no1) {

		Rational simpd = no1;
		
		// Instantiate max interger for iteration
		int min = abs(no1.numerator);
		if (abs(no1.denominator < min)) min = no1.denominator;

		int gcf = 1;

		// Check if numerator = 0 (avoid division by 0)
		if (no1.numerator != 0) {

			// Iterate 1 through max (between numerator and denominator) to find greatest common factor
			for (int i = 1; i <= min; i++) {
				if (no1.numerator % i == 0 && no1.denominator % i == 0) gcf = i;
			}

			// Update simplified rational number by dividing by gcf
			simpd.numerator /= gcf;
			simpd.denominator /= gcf;

		}

		return simpd;

	}

}