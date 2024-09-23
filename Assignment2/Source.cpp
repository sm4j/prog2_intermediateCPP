/*
Jordan Small
Professor Taebi
FEB. 5, 2024
Assignment2 - Loan Calculator
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
using namespace std;

void Welcome();
char MakeSelection();
void Collect_Input(double* total, double* rate, int* term);
void Term_Input_Helper(int* term);
double Calc_Monthly_Rate(double rate);
double Calc_Monthly_Payment(double total, double monthly_rate, int term);
void Total_Payments(int term, double total, double monthly_pay, double monthly_rate, double* full_paid, double* interest_paid);
void Display_Totals(int term, double total, double rate, double monthly_pay, double monthly_rate, double full_paid, double interest_paid);
void Amortization_Schedule(int term, double total, double monthly_pay, double monthly_rate);
void Goodbye();

int main() {

	double loan_amount = 0.0, apr = 0.0;
	int loan_term = 0;
	char menu_choice = 'z';
	double monthly_payment = 0.0, monthly_rate = 0.0;
	double total_paid = 0.0, total_interest_paid = 0.0;

	Welcome();

	menu_choice = MakeSelection();

	while (menu_choice != 'Q' && menu_choice != 'q') {

		if (menu_choice == 'c' || menu_choice == 'C') {

			Collect_Input(&loan_amount, &apr, &loan_term);
			monthly_rate = Calc_Monthly_Rate(apr);
			monthly_payment = Calc_Monthly_Payment(loan_amount, monthly_rate, loan_term);

		}

		if (menu_choice == 'd' || menu_choice == 'D') {

			if (loan_amount != 0) {

				Total_Payments(loan_term, loan_amount, monthly_payment, monthly_rate, &total_paid, &total_interest_paid);
				Display_Totals(loan_term, loan_amount, apr, monthly_payment, monthly_rate, total_paid, total_interest_paid);
				
			}

			else {
				cout << endl << "Can not display without loan information. Select 'c' or 'C' to input values." << endl;
			}

		}

		if (menu_choice == 'a' || menu_choice == 'A') {

			if (loan_amount != 0) {
				Amortization_Schedule(loan_term, loan_amount, monthly_payment, monthly_rate);
			}

			else {
				cout << endl << "Can not display without loan information. Select 'c' or 'C' to input values." << endl;
			}

		}

		if (menu_choice == 'n' || menu_choice == 'N') {

			loan_amount = 0, apr = 0.0;
			loan_term = 0;
			monthly_payment = 0, monthly_rate = 0.0;

			cout << endl << "All values have been reset to 0. Select 'C' or 'c' to re-calculate based on different input." << endl;

		}

		menu_choice = MakeSelection();

	}

	Goodbye();

	return 0;

}

void Welcome() {

	cout << "*******************************************************" << endl;
	cout << "Welcome to the Loan Calculator! You will be prompted" << endl;
	cout << "to enter your total loan amount (in USD), annual percentage" << endl;
	cout << "rate, and your loan term in months. The program will" << endl;
	cout << "calculate and display the amortization schedule." << endl;
	cout << "*******************************************************" << endl;

}

char MakeSelection() {

	char choice = 'z';

	cout << endl;
	cout << "Please choose from the following menu choices: " << endl;
	cout << "Select 'C' or 'c'... to input values and calculate loan amortization" << endl;
	cout << "Select 'D' or 'd'... to display payment summary" << endl;
	cout << "Select 'A' or 'a'... to display amortization schedule" << endl;
	cout << "Select 'N' or 'n'... to reset all values" << endl;
	cout << "Select 'Q' or 'q'... to QUIT" << endl << endl;

	cin >> choice;

	return choice;

}

void Collect_Input(double* total, double* rate, int* term) {

	cout << endl << "*******************************************************";

	do {

		cout << endl << "Enter total amount of loan: ";
		cin >> *total;

		if (*total < 0) {
			cout << endl << "The principal loan amount can not be a negative number." << endl;
		}

	} while (*total < 0);

	do {

		cout << "Enter annual percentage rate (APR): ";
		cin >> *rate;

		if (*rate < 0 || *rate > 100) {
			cout << endl << "The APR needs to be a value between 1 and 100." << endl;
		}

	} while (*rate < 0 || *rate > 100);


	do {

		Term_Input_Helper(term);

	} while (*term < 0 || *term > 360);

	cout << endl << "All values have been recorded. You can now view the" << endl;
	cout << "payment summary and/or a tabular amortization schedule." << endl;
	cout << "*******************************************************" << endl;

}

void Term_Input_Helper(int *term) {

	char help_choice = 'z';

	cout << endl;

	do {

		cout << "Select 'M' or 'm'... to enter your term in MONTHS" << endl;
		cout << "Select 'Y' or 'y'... to enter your term in YEARS" << endl;
		cin >> help_choice;
		cout << endl;

		if (help_choice == 'M' || help_choice == 'm') {
			cout << "Please enter your term length in MONTHS (30 year max): ";
			cin >> *term;
		}

		if (help_choice == 'Y' || help_choice == 'y') {
			cout << "Please enter your term length in YEARS (30 year max): ";
			cin >> *term;
			*term *= 12;
		}

		if (*term < 0) {
			cout << endl << "The term length can not be a negative number." << endl;
		}

		if (*term > 360) {
			cout << endl << "The term length can not exceed 30 years." << endl;
		}

	} while (help_choice != 'M' && help_choice != 'm' && help_choice != 'y' && help_choice != 'Y');

}

double Calc_Monthly_Rate(double rate) {

	double monthly_rate = pow(1 + rate / 100, 1.0/12);
	return monthly_rate - 1;

}

double Calc_Monthly_Payment(double total, double monthly_rate, int term) {

	double monthly_payment = total * monthly_rate * pow(1 + monthly_rate, term) / (pow(1 + monthly_rate, term) - 1);
	return monthly_payment;

}

void Total_Payments(int term, double total, double monthly_pay, double monthly_rate, double* full_paid, double* interest_paid) {

	double monthly_interest = total * monthly_rate;
	double monthly_principal = monthly_pay - monthly_interest;
	*interest_paid = monthly_interest;
	*full_paid = term * monthly_pay;

	for (int i = 1; i <= term; i++) {

		total = total - monthly_principal;
		monthly_interest = total * monthly_rate;
		monthly_principal = monthly_pay - monthly_interest;
		*interest_paid = *interest_paid + monthly_interest;

	}

}

void Display_Totals(int term, double total, double rate, double monthly_pay, double monthly_rate, double full_paid, double interest_paid) {

	cout << endl;
	cout << "*******************************************************" << endl;
	cout << "Initial Loan Amount: \t\t\t" << "$" << fixed << setprecision(2) << total << endl;
	cout << "Annual Percentage Rate (APR): \t\t" << rate << "%" << endl;
	cout << "Number of months in the loan term: \t" << term << endl << endl;

	cout << "Monthly interest percentage: \t\t" << fixed << setprecision(7) << monthly_rate << "%" << endl;
	cout << "Monthly paymment amount: \t\t" << "$" << fixed << setprecision(2) << monthly_pay << endl << endl;

	cout << "Total paid through life of loan: \t" << "$" << full_paid << endl;
	cout << "Total paid in interest: \t\t" << "$" << interest_paid << endl;

	cout << "*******************************************************" << endl;

}

void Amortization_Schedule(int term, double total, double monthly_pay, double monthly_rate) {

	double monthly_interest = total * monthly_rate;
	double monthly_principal = monthly_pay - monthly_interest;
	double balance = total - monthly_principal;

	cout << endl << "************************ Total Monthly Payment ($" << fixed << setprecision(2) <<  monthly_pay << ") ************************" << endl;

	cout << "+-----------+------------------+---------------+--------------+-----------------+" << endl;
	cout << "|   Month   |   Start Balance  |   Principal   |   Interest   |   End Balance   | " << endl;
	cout << "+-----------+------------------+---------------+--------------+-----------------+" << endl;
	cout << "| " << fixed << setprecision(2) << setw(9) << "1" << " | $" << setw(15) << total << " | $" << setw(12) << monthly_principal << " | $" << setw(11) << monthly_interest << " | $" << setw(14) << balance << " |" << endl;

	
	for (int i = 2; i <= term; i++) {
		
		total -= monthly_principal;
		monthly_interest = total * monthly_rate;
		monthly_principal = monthly_pay - monthly_interest;
		balance -= monthly_principal;

		cout << "| " << fixed << setprecision(2) << setw(9) << i << " | $" << setw(15) << total << " | $" << setw(12) << monthly_principal << " | $" << setw(11) << monthly_interest << " | $" << setw(14) << balance << " |" << endl;

		if (i == term) {
			balance = 0.0;
		}

		if (i % 12 == 0) {
			int padding = (i/12 < 10) ? 34 : 33;

			cout << "|-------------------------------------------------------------------------------|" << endl;
			cout << "| " << setw(40) << "Year #" << i / 12 << " End" << setw(padding) << "|" << endl;
			cout << "|-------------------------------------------------------------------------------|" << endl;
		}

	}

}

void Goodbye() {

	cout << endl << "Thanks for participating! Have a great day!" << endl << endl;
                                                                                                                                               
	cout << "                                                                      ddddddd       bbbbbbb                                                          " << endl;
	cout << "         GGGGGGGGGGGGG                                                d:::::d       b:::::b                                                    !!!   " << endl;
	cout << "       GGG::::::::::::G                                               d:::::d       b:::::b                                                   !!::!  " << endl;
	cout << "      GG:::::::::::::::G                                              d:::::d       b:::::b                                                   !:::!  " << endl;
	cout << "     G:::::GGGGGGGG::::G                                              d:::::d       b:::::b                                                   !:::!  " << endl;
	cout << "    G:::::G       GGGGGG   ooooooooooo     ooooooooooo        ddddddddd:::::d       b:::::bbbbbbbbb yyyyyyy           yyyyyyy eeeeeeeeeeee    !:::!  " << endl;
	cout << "   G:::::G               oo:::::::::::o ooo:::::::::::oo    dd::::::::::::::d       b::::::::::::::bby:::::y         y:::::yee::::::::::::ee  !:::!  " << endl;
	cout << "   G:::::G              o:::::::::::::::oo:::::::::::::::o d::::::::::::::::d       b::::::::::::::::by:::::y       y:::::ye::::::eeeee:::::ee!:::!  " << endl;
	cout << "   G:::::G    GGGGGGGGGGo:::::ooooo:::::oo:::::ooooo:::::od:::::::ddddd:::::d       b:::::bbbbb:::::::by:::::y     y:::::ye::::::e     e:::::e!:::!  " << endl;
	cout << "   G:::::G    G::::::::Go::::o     o::::oo::::o     o::::od::::::d    d:::::d       b:::::b    b::::::b y:::::y   y:::::y e:::::::eeeee::::::e!:::!  " << endl;
	cout << "   G:::::G    GGGGG::::Go::::o     o::::oo::::o     o::::od:::::d     d:::::d       b:::::b     b:::::b  y:::::y y:::::y  e:::::::::::::::::e !:::!  " << endl;
	cout << "   G:::::G        G::::Go::::o     o::::oo::::o     o::::od:::::d     d:::::d       b:::::b     b:::::b   y:::::y:::::y   e::::::eeeeeeeeeee  !!:!!  " << endl;
	cout << "    G:::::G       G::::Go::::o     o::::oo::::o     o::::od:::::d     d:::::d       b:::::b     b:::::b    y:::::::::y    e:::::::e            !!!   " << endl;
	cout << "     G:::::GGGGGGGG::::Go:::::ooooo:::::oo:::::ooooo:::::od::::::ddddd::::::d       b:::::bbbbbb::::::b     y:::::::y     e::::::::e                 " << endl;
	cout << "      GG:::::::::::::::Go:::::::::::::::oo:::::::::::::::od:::::::::::::::::d       b::::::::::::::::b       y:::::y       e::::::::eeeeeeee   !!!   " << endl;
	cout << "        GGG::::::GGG:::G oo:::::::::::oo  oo:::::::::::oo  d:::::::::ddd::::d       b:::::::::::::::b       y:::::y         ee:::::::::::::e  !!:!!  " << endl;
	cout << "           GGGGGG   GGGG   ooooooooooo      ooooooooooo      ddddddddd  ddddd       bbbbbbbbbbbbbbbb       y:::::y            eeeeeeeeeeeeee   !!!   " << endl;
	cout << "                                                                                                          y:::::y                                    " << endl;
	cout << "                                                                                                         y:::::y                                     " << endl;
	cout << "                                                                                                        y:::::y                                      " << endl;
	cout << "                                                                                                       y:::::y                                       " << endl;
	cout << "                                                                                                      yyyyyyy                                        " << endl;
                                                                                                                                                                                                                                                                                     
}