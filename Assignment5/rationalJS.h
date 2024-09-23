/*

Jordan Small
Assignment 5
4 APR 2024

Header file rationalJS.h: This is the interface for the class Rational.
Values of this type are rational numbers. There are several input cases,
but the output will be expressed as a rational number (X/Y). Member
functions in this file are declared to overload operators useful for
rational algebra such as addition, multiplication, subtraction, division,
and equality statements.

*/

// Pre-processor headers ensure that only onne definition
// of the class is allowed
#ifndef RATIONALJS_H
#define RATIONALJS_H

#include <iostream>
using namespace std;

namespace RATIONAL_SMALL {

	class Rational {

	private:

		int numerator = -1;
		int denominator = -1;

	public:

		// Constructors
		Rational();
		Rational(int num);
		Rational(int num, int den);

		// Getters
		int getNum(const Rational no1);
		int getDen(const Rational no1);

		// I/O Overload
		friend istream& operator >>(istream& in, Rational& no1);
		friend ostream& operator <<(ostream& out, const Rational& no1);

		// Binary algebraic operator overload
		friend Rational operator +(const Rational no1, const Rational no2);
		friend Rational operator -(const Rational no1, const Rational no2);
		friend Rational operator *(const Rational no1, const Rational no2);
		friend Rational operator /(const Rational no1, const Rational no2);

		// Unary algebraic operator overload
		friend Rational operator -(const Rational no1);

		// Equality operator overload
		friend bool operator >(const Rational no1, const Rational no2);
		friend bool operator <(const Rational no1, const Rational no2);
		friend bool operator ==(const Rational no1, const Rational no2);
		friend bool operator !=(const Rational no1, const Rational no2);
		friend bool operator >=(const Rational no1, const Rational no2);
		friend bool operator <=(const Rational no1, const Rational no2);

		// Helper function, taking a Rational object as a parameter
		// returning a simplified Rational object as output
		// (if d%n == 0)
		friend Rational simplify(const Rational& no1);

	};

}

#endif // RATIONALJS_H