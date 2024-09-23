/*

Assignment 6
Jordan Small
16 APR, 2024

This assignment uses the Lecture19.cpp as a skeleton in order to add
functionality to the StringVar class created as a group. Member functions
that have been added include: copy_piece, one_char, set_char, and overloads
for operators ==, +, and >>.

*/

//This is the definition for the class StringVar
//whose values are strings. An object is declared as follows.
//Note that you use (max_size), not [max_size]
//StringVar the_object(max_size);
//where max_size is the longest string length allowed.

#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <iostream>

using namespace std;

class StringVar {

public:

    StringVar(int size1);
    //Initializes the object so it can accept string values up to size
    //in length. Sets the value of the object equal to the empty string.

    StringVar();
    //Initializes the object so it can accept string values of length 100
    //or less. Sets the value of the object equal to the empty string.

    StringVar(const char a[]);
    //Precondition: The array a contains characters terminated with '\0'.
    //Initializes the object so its value is the string stored in a and
    //so that it can later be set to string values up to strlen(a) in length.

    StringVar(const StringVar& string_object);
    //Copy constructor.

    ~StringVar();
    //Returns all the dynamic memory used by the object to the freestore.

    int length() const;
    //Returns the length of the current string value.

    void input_line(istream& ins);
    //Precondition: If ins is a file input stream, then ins has been
    //connected to a file.
    //Action: The next text in the input stream ins, up to '\n', is copied
    //to the calling object. If there is not sufficient room, then
    //only as much as will fit is copied.

    friend ostream& operator <<(ostream& outs, const StringVar& the_string);
    //Overloads the << operator so it can be used to output values
    //of type StringVar
    //Precondition: If outs is a file output stream, then outs
    //has already been connected to a file.

    //////////////////// BELOW THIS LINE ARE MEMBER FUNCTIONS FOR ASSIGNMENT 6 ////////////////////////

    StringVar copy_piece(char* location, int n);
    // Copies a specified substring fom a given location
    // Char pointer paramter: a pointer to the starting position of the substring
    // Int paramter: the number of characters to copy
    // Returns a string containing the specified substring

    char one_char(int location) const;
    // Returns char at specified location
    // Int parameter: index to return

    void set_char(int location, char replace);
    // Changes a char at a given location with specified char

    friend bool operator ==(const StringVar comp1, const StringVar comp2);
    // Checks equality between two StringVars
    // Returns true or false

    friend StringVar operator +(const StringVar one, const StringVar two);
    // Overloads the + operator to concatenate two StringVar objects
    // Parameters are the two StringVar objects to add

    friend istream& operator >>(istream& ins, StringVar& str);
    // Overloads the extraction operator >> to read one word into the StringVar object
    // istream parameter, ins, is the stream to read from

private:

    char* value; //pointer to dynamic array that holds the string value.
    int max_length; //declared max length of any string value.

};

void conversation(int max_name_size);
//Carries on a conversation with the user.

int main() {

    conversation(30);
    cout << "End of demonstration." << endl << endl;

    // Test copy_piece function
    char test[] = "example text";
    StringVar str;

    StringVar result = str.copy_piece(&test[3], 4);
    cout << result << endl << endl;

    // Test one_char function
    StringVar app("apple pie");
    cout << app.one_char(4) << endl << endl;

    // Test set_char function
    app.set_char(4, 'u');
    cout << app << endl << endl;

    // Test overloaded == operator
    StringVar p("peanut");
    StringVar p2("peanut");
    StringVar b("butter");
    cout << (p == p2) << endl << endl;
    cout << (p == b) << endl << endl;

    // Test overloaded + operator
    StringVar pb = p + b;
    cout << pb << endl << endl;

    // Test overloaded extraction >> operator
    cout << "Enter a word: " << endl;
    StringVar in;
    cin >> in;
    cout << "Your word is: " << in;

    return 0;

}

//This is only a demonstration function
void conversation(int max_name_size) {

    StringVar your_name(max_name_size), our_name("Anita");

    cout << "What is your name?\n";
    your_name.input_line(cin);
    cout << "We are " << our_name << endl;
    cout << "We will meet again " << your_name << endl;

}

//Uses cstddef and cstdlib:
StringVar::StringVar(int size1) {

    max_length =size1;
    value = new char[max_length + 1];//+1 is for '\0'.
    value[0] = '\0';

}

//Uses cstddef and cstdlib:
StringVar::StringVar( ) {

    max_length=100;
    value = new char[max_length + 1];//+1 is for '\0'.
    value[0] = '\0';

}

//Uses cstring, cstddef, and cstdlib:
StringVar::StringVar(const char a[]) {

    max_length = strlen(a);
    value = new char[max_length + 1];//+1 is for '\0'.
    strcpy(value,a);

}

//Uses cstring, cstddef, and cstdlib:
StringVar::StringVar(const StringVar& string_object) {

    max_length = string_object.length( );
    value = new char[max_length + 1];//+1 is for '\0'.
    strcpy(value, string_object.value);

}

StringVar::~StringVar( ){
    delete [] value;
}

//Uses cstring:
int StringVar::length( ) const {
    return strlen(value);
}

//Uses iostream:
void StringVar::input_line(istream& ins) {
    ins.getline(value, max_length + 1);
}

//Uses iostream:
ostream& operator <<(ostream& outs, const StringVar& the_string) {
    outs << the_string.value;
    return outs;
}

StringVar StringVar::copy_piece(char* location, int n) {

    // Create a temporary dynamic array to store the substring
    char* substring = new char[n + 1];

    // Copy n characters from the specified location and set last char to null
    strncpy(substring, location, n);
    substring[n] = '\0';

    // Create a string object from the substring
    StringVar result(substring);

    // Delete dynamic array
    delete[] substring;

    return result;
}

char StringVar::one_char(int location) const {
    
    // Check if the location is within bounds
    // if so - return char at that location
    if (location >= 0 && location < length()) {
        return value[location];
    }

    // otherwise return null character
    else return '\0';
}

void StringVar::set_char(int location, char replace) {

    // Check if the location is within bounds
    // if so - replace char with replace
    if (location >= 0 && location < length()) {
        value[location] = replace;
    }

}

bool operator ==(const StringVar comp1, const StringVar comp2) {
    // Check if string values are equal
    return strcmp(comp1.value, comp2.value) == 0;
}

StringVar operator +(const StringVar one, const StringVar two) {

    // Calculate length of concatenated string
    int newL = one.length() + two.length();

    // Allocate memory for new string
    char* concString = new char[newL + 1];

    // Copy the contents of first string
    strcpy(concString, one.value);

    // Concatenate the string from the second object
    strcat(concString, two.value);

    // Instantiate a new StringVar object with the concatenated string
    StringVar result(concString);

    // Delete dynamic array
    delete[] concString;

    // Return concatenated StringVar object
    return result;

}

istream& operator >>(istream& ins, StringVar& str) {
    
    // Reads one word into the value member
    ins >> str.value;
    return ins;

}