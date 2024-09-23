/*
COP3014: Programming II
Assignment1 - Jordan Small
Instructor: Sarah Taebi
"Genereate a coin dispenser machine that
dispenses the least number of equivalent 
coins, based on the U.S. coin system."
JAN 19, 2023
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

// Function prototypes
double Welcome();
int Convert_to_Pennies(double input);
void Coin_Breakdown(int total_pennies, double input);
void Goodbye();

// Constant interger declarations/initializations
const int QUARTER = 25;
const int DIME = 10;
const int NICKEL = 5;
const int PENNY = 1;

int main() {

	double input_value = Welcome();

	int total_pennies = Convert_to_Pennies(input_value);

	Coin_Breakdown(total_pennies, input_value);

	Goodbye();

	return 0;

}

// Function displays a welcome message and returns a double, used as the input value in main
double Welcome() {

	// Declare and initialize input variable
	double input = 0;

	cout << "---------------------------------------------------------------------------------------\n";
	cout << "Welcome to the Coin Dispenser.\n";
	cout << "You will be prompted to enter an amount in $xx.yy format ($100 max).\n";
	cout << "A breakdown will be given of the least amount of coins necessary to fulfill your order.\n";
	cout << "---------------------------------------------------------------------------------------\n\n";

	// Prompt and get input value from user in xx.yy format
	cout << "Please enter your input ammount in $xx.yy format ($100 max) and hit enter: ";
	cin >> input;

	// Test to make sure input is between 0 and 100; if not-- exit
	if (input < 0.0 || input > 100.0) {

		cout << "\nInvalid amount... aborting!\n";
		exit(1);

	}

	return input;

}

// Function takes one double parameter (input in main function) and returns its value (times 100) as an int
int Convert_to_Pennies (double input) {

	// Use the round function by including the cmath library, in order to round to the nearest whole number
	// This makes the conversion to intergers much more accurate
	double pennies_in_double = round(input * 100.0);
	int pennies_in_int = (int)pennies_in_double;
	
	return pennies_in_int;

}

// Function takes one interger and one double parameter and uses constant values to breakdown into coins based on USD system
// Function displays the breakdown with initial input value and returns void
void Coin_Breakdown(int total_pennies, double input) {

	// Math using division and modular operator to determine amount of coins
	int quarters = (total_pennies / QUARTER);
	int change1 = total_pennies % QUARTER;
	int dimes = change1 / DIME;
	int change2 = change1 % DIME;
	int nickels = change2 / NICKEL;
	int pennies = change2 % NICKEL;

	cout << "\n******** CHANGE DISPENSED ********\n\n";
	cout << "Value: \t\t" << "$" << input;
	cout << "\nQuarters:\t" << quarters;
	cout << "\nDimes: \t\t" << dimes;
	cout << "\nNickels: \t" << nickels;
	cout << "\nPennies: \t" << pennies;
	cout << "\n\n***********************************\n";

}

// Function displays a goodbye message
void Goodbye() {

	cout << "\nThanks for participating and have a great day!\n";

}