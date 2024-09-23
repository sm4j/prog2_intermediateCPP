/*
Jordan Small
15 MAR, 2024
Professor Taebi

Assignment 4: This assignment focuses on encapsalation. A base and
derived class (COP3014 and Spring24, respectively) are generated 
in order to keep track of student information in the class. Member 
functions for these ADT's include constructors, setters, getters, 
mutators, and data attributes.
*/

// Include necessary libraries
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

// Parent class
class COP3014 {

private:

	string first = "None";
	string last = "None";
	long int zNumber = -1;
	double assignments[4] = { -1, -1, -1, -1 };
	double midterm = -1;
	double final = -1;
	double totalGrade = 100.0;
	string finalLetter = "A";

public:

	// Constructors
	COP3014();
	COP3014(string fname, string lname, int z);

	// Setters
	void setZNumber(int num);
	void setAssignments(double g1, double g2, double g3, double g4);
	void setMidterm(double grade);
	void setFinal(double grade);
	void setName(string f, string l);

	// I/O
	void userInput();
	void displayInfo(ostream& outs);

	// Getters
	string getFirst();
	string getLast();
	double getMidterm();
	double getFinal();
	int getZnumber();

	double getAssign1();
	double getAssign2();
	double getAssign3();
	double getAssign4();

	// Mutators/Calculations
	double getTotal();
	string getLetter();

};

class Spring24 : public COP3014 {

private:

	double lab = 0.0;
	
public:

	// Constructors
	Spring24();
	Spring24(string fname, string lanme, int z);

	// Setters (not inherited)
	void setLab(double grade);

	// I/O
	void userInput();
	void displayInfo(ostream& outs);

	// Getters (not inherited)
	double getLab();

	// Mutators/Calculations (overridden from base class)
	double getTotal();
	string getLetter();

};

// Function prototype for helper function (described in definition)
string nTH(double grade);

int main() {

	// Debugging/testing

	// Object instantiation
	COP3014 test; //defualt constructor
	COP3014 test2("John", "Doe", 324345); //constructor with 3 parameters
	Spring24 spring, spring2;

	// I/O testing
	cout << "Default COP3014 object construction displayInfo: " << endl << endl;
	test2.displayInfo(cout);

	cout << endl;
	test2.setFinal(100);

	cout << "Object displayInfo after setFinal(100);" << endl << endl;
	test2.displayInfo(cout);

	cout << endl << "User input for COP3014 object: " << endl << endl;
	test.userInput();
	cout << endl << "displayInfo after input: " << endl << endl;
	test.displayInfo(cout);

	cout << endl << "User input for Spring24 object: " << endl << endl;
	spring.userInput();
	cout << endl << "displayInfo after input: " << endl;
	spring.displayInfo(cout);

	// Setter testing
	spring2.setName("John", "Doe");
	spring2.setZNumber(2349848);
	spring2.setAssignments(90, 85, 60, 88);
	spring2.setMidterm(85);
	spring2.setFinal(100);
	spring2.setLab(76);
	cout << endl << "displayInfo after setting all attributes: " << endl;
	spring2.displayInfo(cout);

	cout << endl << "Setting attributes outside of bounds (expecting exit): " << endl << endl;
	test2.setAssignments(90, -3, 90, 90); // Invalid input, expect exit
	test2.setMidterm(194); // Comment this line or line above to test either

	return 0;

}

// Default constructor
COP3014::COP3014() {};

// Constructor given 3 parameters
COP3014::COP3014(string fname, string lname, int z) {
	first = fname;
	last = lname;
	zNumber = z;
}

// Setters (Lines 162-226)
// All setters check for valid input before setting
// Exit if input is invalid
void COP3014::setName(string f, string l) {
	first = f;
	last = l;
}
void COP3014::setZNumber(int num) {

	if (num < 0 || num > 99999999) {
		cout << "zNumber needs to be between 1-8 digits!";
		exit(1);
	}

	zNumber = num;

}

void COP3014::setAssignments(double g1, double g2, double g3, double g4) {

	if (g1 < 0 || g1 > 100) {
		cout << "Grades must be between 0 and 100!";
		exit(1);
	}

	if (g2 < 0 || g2 > 100) {
		cout << "Grades must be between 0 and 100!";
		exit(1);
	}

	if (g3 < 0 || g3 > 100) {
		cout << "Grades must be between 0 and 100!";
		exit(1);
	}

	if (g2 < 0 || g3 > 100) {
		cout << "Grades must be between 0 and 100!";
		exit(1);
	}

	assignments[0] = g1;
	assignments[1] = g2;
	assignments[2] = g3;
	assignments[3] = g4;

}

void COP3014::setMidterm(double grade) {

	if (grade < 0 || grade > 100) {
		cout << "Grades must be between 0 and 100!";
		exit(1);
	}

	midterm = grade;

}

void COP3014::setFinal(double grade) {

	if (grade < 0 || grade > 100) {
		cout << "Grades must be between 0 and 100!";
		exit(1);
	}

	final = grade;

}

// Input function for all attributes
// Also performs checks to make sure input is within range
void COP3014::userInput() {

	cout << "Enter first name: ";
	cin >> first;
	cout << "Enter last name: ";
	cin >> last;

	do {

		cout << "Enter Znumber (without letter Z): ";
		cin >> zNumber;

		if (zNumber < 0 || zNumber > 99999999) {
			cout << "zNumber needs to be between 1-8 digits!" << endl;
		}

	} while (zNumber < 0 || zNumber > 99999999);

	for (int i = 0; i < 4; i++) {
		do {
			cout << "Enter assignment [" << i + 1 << "] grade: ";
			cin >> assignments[i];
			if (assignments[i] < 0 || assignments[i] > 100) {
				cout << "Grades must be between 0 and 100!" << endl;
			}
		} while (assignments[i] < 0 || assignments[i] > 100);
	}
	
	do {
		cout << "Enter midterm grade: ";
		cin >> midterm;
		if (midterm < 0 || midterm > 100) {
			cout << "Grades must be between 0 and 100!" << endl;
		}
	} while (midterm < 0 || midterm > 100);

	do {
		cout << "Enter final exam grade: ";
		cin >> final;
		if (final < 0 || final > 100) {
			cout << "Grades must be between 0 and 100!" << endl;
		}
	} while (final < 0 || final > 100);

}

// Getters (Lines 277-311)
string COP3014::getFirst() {
	return first;
}

string COP3014::getLast() {
	return last;
}

double COP3014::getMidterm() {
	return midterm;
}

double COP3014::getFinal() {
	return final;
}

int COP3014::getZnumber() {
	return zNumber;
}

double COP3014::getAssign1() {
	return assignments[0];
}

double COP3014::getAssign2() {
	return assignments[1];
}

double COP3014::getAssign3() {
	return assignments[2];
}

double COP3014::getAssign4() {
	return assignments[3];
}

// getTotal computes and returns the total grade
double COP3014::getTotal() {

	double grade = (((assignments[0] + assignments[1] + assignments[2] + assignments[3]) / 4.0) * 0.25 + (midterm * 0.3) + (final * 0.45));

	// If no grades are inputted, return 100 (default until grades are added)
	if (getFinal() == -1 && getMidterm() == -1 && getAssign1() == -1 && getAssign2() == -1 && getAssign3() == -1 && getAssign4() == -1) {
		return 100.0;
	}

	// If student is absent for final, highest possible grade is 50
	if (final == 0 && grade > 50) {
		return 50.0;
	}

	else return grade;

}

// getLetter returns the letter grade, best on getTotal
string COP3014::getLetter() {

	// The grade is rounded up and casted to an interger in order to return letter grade
	double g = round(getTotal());
	int grade = (int)g;

	
	if (grade > 89) {
		return "A";
	}

	if (grade > 86 && grade < 90) {
		return "A-";
	}

	if (grade > 82 && grade < 87) {
		return "B+";
	}

	if (grade > 79 && grade < 83) {
		return "B";
	}

	if (grade > 76 && grade < 80) {
		return "B-";
	}

	if (grade > 72 && grade < 77) {
		return "C+";
	}

	if (grade > 69 && grade < 73) {
		return "C";
	}

	if (grade > 66 && grade < 70) {
		return "C-";
	}

	if (grade > 62 && grade < 67) {
		return "D+";
	}

	if (grade > 59 && grade < 63) {
		return "D";
	}

	if (grade > 50 && grade < 60) {
		return "D-";
	}

	else return "F";

}

// Output/display function
void COP3014::displayInfo(ostream& outs) {
	
	// All grades are passed to "not taken helper (nTH)"
	// If any grade = -1 (default value), "Not yet taken" will be
	// outputted, rather than -1.

	outs << first << " " << last << " - " << "Z" << zNumber << endl;
	for (int i = 0; i < 4; i++) {
		outs << "\tAssignment [" << i + 1 << "]: " << nTH(assignments[i]) << endl;
	}
	outs << "\tMidterm: " << nTH(midterm) << endl;
	outs << "\tFinal: " << nTH(final) << endl;
	outs << "\tTotal grade: " << getTotal() << endl;
	outs << "\tFinal grade: " << getLetter() << endl;

}

// Constructors for derived class
Spring24::Spring24() : COP3014() {};

Spring24::Spring24(string fname, string lname, int z) : COP3014(fname, lname, z) {};

// Additional setter for new data attribute in derived class
// Checks for valid input before setting
// Exit if input is invalid
void Spring24::setLab(double grade) {

	if (grade < 0 || grade > 100) {
		cout << "Grades must be between 0 and 100!";
		exit(1);
	}

	lab = grade;

}

// userInput is overriden from its parent class
void Spring24::userInput() {

	// The base class's userInput function is called as
	// there is only one more attribute to display, which
	// is appended below this call.
	COP3014::userInput();

	do {
		cout << "Enter lab grade: ";
		cin >> lab;
		if (lab < 0 || lab > 100) {
			cout << "Grades must be between 0 and 100!" << endl;
		}
	} while (lab < 0 || lab > 100);

}

// Getter for additional attribute in derived class
double Spring24::getLab() {
	return lab;
}

// getTotal is overriden from its parent class and redefined
double Spring24::getTotal() {

	// Variables are created and assigned values from
	// getter functions, in order to access private
	// member functions from its parent class
	
	double g[4] = { getAssign1(), getAssign2(), getAssign3(), getAssign4() };
	double mt = getMidterm();
	double fin = getFinal();

	// The grade in the derived class is calculated differently
	double grade = (((g[0] + g[1] + g[2] + g[3]) / 4) * 0.25 + mt * 0.25 + fin * 0.4 + lab * 0.1);

	// If no grades are inputted, return 100 (default until grades are added)
	if (fin == -1 && mt == -1 && g[0] == -1 && g[1] == -1 && g[2] == -1 && g[3] == -1) {
		return 100.0;
	}

	// If student is absent for final, highest possible grade is 50
	if (fin == 0 && grade > 50) {
		return 50.0;
	}

	// If student is absent for midterm, highest possible grade is a C (72)
	else if (mt == 0 && grade > 73) {
		return 72.0;
	}

	else return grade;

}

// getLetter returns the letter grade, best on getTotal
// this function is overriden/redefined from its base class
// as the calculation (getTotal()) was redefined as well.
string Spring24::getLetter() {

	// The grade is rounded up and casted to an interger in order to return letter grade
	double g = getTotal();
	double grade = (int)g;

	if (grade > 89) {
		return "A";
	}

	if (grade > 86 && grade < 90) {
		return "A-";
	}

	if (grade > 82 && grade < 87) {
		return "B+";
	}

	if (grade > 79 && grade < 83) {
		return "B";
	}

	if (grade > 76 && grade < 80) {
		return "B-";
	}

	if (grade > 72 && grade < 77) {
		return "C+";
	}

	if (grade > 69 && grade < 73) {
		return "C";
	}

	if (grade > 66 && grade < 70) {
		return "C-";
	}

	if (grade > 62 && grade < 67) {
		return "D+";
	}

	if (grade > 59 && grade < 63) {
		return "D";
	}

	if (grade > 50 && grade < 60) {
		return "D-";
	}

	else return "F";

}

void Spring24::displayInfo(ostream& outs) {

	// Variables are created and assigned values from
	// getter functions, in order to access private
	// member functions from its parent class

	string first = getFirst();
	string last = getLast();

	int zNumber = getZnumber();
	double g[4] = { getAssign1(), getAssign2(), getAssign3(), getAssign4() };

	double mt = getMidterm();
	double fin = getFinal();

	// All grades are passed to "not taken helper (nTH)"
	// If any grade = -1 (default value), "Not yet taken" will be
	// outputted, rather than -1.

	outs << endl;
	outs << first << " " << last << " - " << "Z" << zNumber << endl;
	for (int i = 0; i < 4; i++) {
		outs << "\tAssignment [" << i + 1 << "]: " << nTH(g[i]) << endl;
	}
	outs << "\tMidterm: " << nTH(mt) << endl;
	outs << "\tFinal: " << nTH(fin) << endl;
	outs << "\tLab: " << nTH(lab) << endl;
	outs << "\tTotal grade: " << getTotal() << endl;
	outs << "\tFinal grade: " << getLetter() << endl;

}

// "Not-taken helper"
// Default grade values for this object are set to -1 (not taken)
// This function is a helper that will display "Not yet taken"
// instead of "-1" in display member functions
string nTH(double grade) {
	
	if (grade == -1) {
		return "Not yet taken";
	}

	else return to_string(grade);

}