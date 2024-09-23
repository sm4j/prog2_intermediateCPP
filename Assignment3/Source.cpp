/*

Jordan Small
Professor Taebi
22 FEB, 2024

Assignment 3: The goal of this assignment is to randomly generate
N quiz scores (0-10) ranging from Q (1-20). The program prompts
the user for an amount of students to enter and allows them to
enter first and last name, before randomly generating the aforementioned
parameters. Once done, these values are stored to the input file
and copied to the output file, where the average for each
student is appended to each line.

*/


// Include necessary libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Set constant for max students/quiz scores
const int maxNo = 10;

// Constructed a struct for students
struct Student {

	string fname = "";
	string lname = "";
	int noQuiz = 0;
	int scores[maxNo] = {};
	double avg = 0;

};

///// Function prototypes /////

// welcome returns a string (the name of the input file) and opens
// the file for both the input and output stream
string welcome(ifstream& input, ofstream& output);

// randQuizAmt returns a random int [0,10]
int randQuizAmt();

// randScore returns a random int [1,20]
int randScore();

// fillStudent returns a student object, prompting user to enter
// fname and lname and randomly generates noQuiz and scores
Student fillStudent();

// inputData prompts for amount of students to enter, before looping
// that amount to enter data for students
void inputData(ofstream& input, int& students, Student list[]);

// average returns an average for array of intergers that is passed
double average(int scores[]);

// outputData reads and copies the input file line by line and outputs
// it to the output file, followed by the average for each student
void outputData(ofstream& output, ifstream& input, Student list[]);

// goodbye displays a goodbye message, including the name of the files
// that were updated and the amount of students added
void goodbye(string in, string out, int no);

int main() {

	// construct necessary variables
	ifstream in;
	ofstream out;
	Student list[maxNo];
	int noStudents = 0;

	// seed for random number generation
	srand(time(0));

	// store the names of the input/output files
	string inFileName = welcome(in, out);
	string outFileName = "output.txt";

	inputData(out, noStudents, list);
	
	// close the first file that we output to (input.txt)
	out.close();

	out.open(outFileName);
	outputData(out, in, list);

	// close files
	out.close();
	in.close();

	goodbye(inFileName, outFileName, noStudents);

	return 0;

}

string welcome(ifstream& input, ofstream& output) {

	// prompt and get input filename from user
	string fileName;
	
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "Welcome to the grade average calculator." << endl;
	cout << "This program will generate random scores for a random amount of quizzes" << endl;
	cout << "for each student. Their names and scores will be stored in an input file," << endl;
	cout << "which will later be read and copied to an output file, also containing" << endl;
	cout << "the average grade for each student." << endl;
	cout << "-------------------------------------------------------------------------------" << endl << endl;

	cout << "Please input the name of the input file (with extension) to continue." << endl;
	cin >> fileName;

	input.open(fileName);

	// test if input file exists
	if (input.fail()) {
		cout << endl << "Error opening '" << fileName << "'" << endl;
		exit(1);
	}

	cout << endl << "File opened successfully!" << endl;
	cout << endl << "-------------------------------------------------------------------------------" << endl;

	output.open(fileName);

	// store the value of the input file name
	return fileName;

}

int randQuizAmt() {

	int n = rand() % 11;
	return n;

}

int randScore() {

	int n = (rand() % 20) + 1;
	return n;

}

Student fillStudent() {

	// construct temp student
	Student temp;

	// prompt and get first and last name
	cout << "Enter first name: ";
	cin >> temp.fname;

	cout << "Enter last name: ";
	cin >> temp.lname;

	cout << endl;

	// generate random amount of quizzes for each student
	temp.noQuiz = randQuizAmt();

	// use random quiz number to generate random grades on each
	for (int i = 0; i < temp.noQuiz; i++) {
		temp.scores[i] = randScore();
	}

	return temp;

}

void inputData(ofstream& input, int& students, Student list[]) {

	// test for amount of students: -1 < students < maxNo const
	do {

		cout << endl << "How many students would you like to input? [" << maxNo << " max]: ";
		cin >> students;
		cout << endl;

		if (students > maxNo) {
			cout << "You can only include " << maxNo << " students in the list." << endl;
		}

		if (students < 0) {
			cout << "There can not be a negative amount of students." << endl;
		}

	} while (students > maxNo || students < 0);

	// fill desired amount of students and print their attribute values
	// in input file
	for (int i = 0; i < students; i++) {
		
		cout << "Student #" << i+1 << endl;
		cout << "------------" << endl;
		list[i] = fillStudent();
		input << list[i].lname << ", " << list[i].fname << " ";

		for (int k = 0; k < list[i].noQuiz; k++) {
			input << list[i].scores[k] << " ";
		}

		input << endl;

	}

}

double average(int scores[]) {

	int sum = 0;
	double localmax = (double)maxNo;

	// iterate through maxNo of quizzes (regardless of their amount
	// taken, avg is to be divided by maxNo)
	for (int i = 0; i < maxNo; i++) {
		sum += scores[i];
	}

	double avg = sum / localmax;

	return avg;

}

void outputData(ofstream& output, ifstream& input, Student list[]) {

	string line;
	int i = 0;

	output << "This file displays the students’ quiz scores along with the average score for each student." << endl << endl;

	// read from input file while there is a string for each line
	while (getline(input, line)) {

		// compute and append average to each student line containing name and scores
		double avg = average(list[i].scores);
		output << fixed << setprecision(2);
		line += ": " + to_string(avg);
		output << line << endl;
		i++;

	}

}

void goodbye(string in, string out, int no) {
	
	// display affected file names and remind user how many students were added
	cout << endl << "-------------------------------------------------------------------------------" << endl;
	cout << "You inputted " << no << " students' grades to '" << in << "' and the output has been saved to '" << out << "'.";
	cout << endl << "Thanks for participating!" << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
}