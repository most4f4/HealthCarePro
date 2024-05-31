#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void) {
    while (getchar() != '\n') {
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void) {
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// validates if the user input is an integer and returns it.
int inputInt(void) {
    int num;
    char ch;
    do {
        scanf("%d%c", &num, &ch);
        if (ch != '\n') {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (ch != '\n');
    return num;
}

// validates if the user input is a positive integer and returns it.
int inputIntPositive(void)
{
    int num2;
    do {
        num2 = inputInt();
        if (num2 <= 0) printf("ERROR! Value must be > 0: ");
    } while (num2 <= 0);
    return num2;
}

// validates if the user entered integer value is within the range provided by two arguments.
int inputIntRange(int low, int high) {
    int num;
    do {
        num = inputInt();
        if (num < low || num > high) printf("ERROR! Value must be between %d and %d inclusive: ", low, high);
    } while (num < low || num > high);
    return num;
}

// validate the entered character matches any of the characters in the received C string argument.
char inputCharOption(const char string[]) {
    char ch, ch1;
    int found = 0;
    do {
        scanf(" %c%c", &ch, &ch1);
        if (ch1 != '\n') {
            clearInputBuffer();
            printf("ERROR: Character must be one of [%s]: ", string);
        }
        else if (!strchr(string, ch)) printf("ERROR: Character must be one of [%s]: ", string);
        else found = 1;
    } while (!found);
    return ch;
}

// validates the entered number of characters is within the specified range.
void inputCString(char string[], int low, int high)
{
    int count;
    do {
        scanf("%[^\n]", string);
        count = strlen(string);
        if (count<low || count>high) {
            if (low == high) printf("ERROR: String length must be exactly %d chars: ", low);
            else if (count > high) printf("ERROR: String length must be no more than %d chars: ", high);
            else printf("ERROR: String length must be between %d and %d chars: ", low, high);
        }
        clearInputBuffer();
    } while (count<low || count>high);

}

// display an array of 10-character digits as a formatted phone number.
void displayFormattedPhone(const char string[])
{
    int i, count, flag;
    count = strlen(string);
    for (i = 0, flag = 0; string[i] != '\0' && flag != 1; i++) {
        if (string[i] < '0' || string[i] > '9') {
            flag = 1;
        }
    }
    if (string == NULL || count != 10 || flag == 1) printf("(___)___-____");
    else         printf("(%c%c%c)%c%c%c-%c%c%c%c", string[0], string[1], string[2], string[3], string[4], string[5], string[6], string[7], string[8], string[9]);
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

//validates the date based on the Gregorian calendar
void isTimeValid(int* year, int* month, int* day) {
    int lastDay = 30;
    printf("Year        : ");
    *year = inputIntPositive();
    printf("Month (1-12): ");
    *month = inputIntRange(1, 12);
    if (*month == 4 || *month == 6 || *month == 9 || *month == 11) lastDay = 30;
    else if (*month == 2) {
        if (*year % 4 == 0 && (*year % 100 != 0 || *year % 400 == 0)) lastDay = 29;
        else lastDay = 28;
    }
    else lastDay = 31;
    printf("Day (1-%d)  : ", lastDay);
    *day = inputIntRange(1, lastDay);
}

// validates the entered number of digits
void inputCStringDigit(char string[], int num )
{
    int count;
    do {
        scanf("%[^\n]", string);
        count = strlen(string);
        if (count != num) printf("Invalid %d-digit number! Number: ", num);
        clearInputBuffer();
    } while (count != num);

}

