#ifndef CORE_H
#define CORE_H

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// validates if the user input is an integer and returns it.
int inputInt(void);

// validates if the user input is a positive integer and returns it.
int inputIntPositive(void);

// validates if the user entered integer value is within the range provided by two arguments.
int inputIntRange(int low, int high);

// validate the entered character matches any of the characters in the received C string argument.
char inputCharOption(const char string[]);

// validates the entered number of characters is within the specified range.
void inputCString(char string[], int low, int high);

// display an array of 10-character digits as a formatted phone number.
void displayFormattedPhone(const char string[]);

//validates the date based on the Gregorian calendar
void isTimeValid(int* year, int* month, int* day);

// validates the entered number of digits
void inputCStringDigit(char string[], int num);

#endif // !CORE_H