#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "core.h"
#include "clinic.h"

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Display's the patient table header (table format)
void displayPatientTableHeader(void) {
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt) {
    if (fmt == FMT_FORM) {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords) {
    printf("Clinic Appointments for the Date: ");
    if (isAllRecords) {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField) {
    if (includeDateField) printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
        appoint->date.day);
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);
    displayFormattedPhone(patient->phone.number);
    printf(" (%s)\n", patient->phone.description);
}

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// main menu
void menuMain(struct ClinicData* data) {
    int selection;
    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection) {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection) printf("Exiting system... Goodbye.\n\n");
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max) {
    int selection;
    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection) {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// Menu: Patient edit
void menuPatientEdit(struct Patient* patient) {
    int selection;
    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);
        displayFormattedPhone(patient->phone.number);
        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        if (selection == 1) {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2) {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }
    } while (selection);
}

// Menu: Appointment Management
void menuAppointment(struct ClinicData* data) {
    int selection;
    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection) {
        case 1:
            viewAllAppointments(data);  
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient); 
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);
            suspend();
            break;
        }
    } while (selection);
}


// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt) {
    int i, recordsFound = 0;
    if (fmt == FMT_TABLE) displayPatientTableHeader();
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber != 0) {
            displayPatientData(&patient[i], fmt);
            recordsFound = 1;
        }
    }
    if (recordsFound != 1) printf("*** No records found ***\n\n");
    printf("\n");
}


// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max) {
    int selection;
    do {
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        printf("\n");
        switch (selection) {
        case 1:
            searchPatientByPatientNumber(patient, max);
            suspend();
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            suspend();
            break;
        }
    } while (selection);

}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max) {
    int index, found = 0;
    for (int i = 0; i < max && found != 1; i++) {
        if (patient[i].patientNumber == 0) {
            index = i;
            found = 1;
        }
    }
    if (found != 1) printf("ERROR: Patient listing is FULL!\n\n");
    else {
        patient[index].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[index]);
        printf("*** New patient record added ***\n\n");
    }
}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max) {
    int num, index;
    printf("Enter the patient number: ");
    num = inputInt();
    printf("\n");
    index = findPatientIndexByPatientNum(num, patient, max);

    if (index == -1) printf("ERROR: Patient record not found!\n");
    else menuPatientEdit(&patient[index]);
}


// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max) {
    int num, index, confirm;
    printf("Enter the patient number: ");
    num = inputInt();
    index = findPatientIndexByPatientNum(num, patient, max);
    printf("\n");
    if (index == -1) printf("ERROR: Patient record not found!\n\n");
    else {
        displayPatientData(&patient[index], FMT_FORM);
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        confirm = inputCharOption("yn");
        if (confirm == 'y') {
            patient[index].patientNumber = 0;
            patient[index].name[0] = '\0';
            patient[index].phone.description[0] = '\0';
            patient[index].phone.number[0] = '\0';
            printf("Patient record has been removed!\n\n");
        }
        else {
            printf("Operation aborted.\n\n");
            clearInputBuffer();
        }
    }
}

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data) {    
    sortAppointment(data->appointments, data->maxAppointments);
    displayScheduleTableHeader(NULL, 1);
    for (int i = 0; i < data->maxAppointments; i++) {
        int patientIndex = findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient);
        if (patientIndex != -1) displayScheduleData(&data->patients[patientIndex], &data->appointments[i], 1);
    } 
    printf("\n");
}


// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data) {
    struct Date date;
    isTimeValid(&date.year, &date.month, &date.day);
    sortAppointment(data->appointments, data->maxAppointments);
    printf("\n");
    displayScheduleTableHeader(&date, 0);
    for (int i = 0; i < data->maxAppointments; i++)  {     
        if (data->appointments[i].date.year == date.year &&
            data->appointments[i].date.month == date.month &&
            data->appointments[i].date.day == date.day) {
            int flag = 1;
            for (int j = 0; j < data->maxPatient && flag == 1; j++) {
                if (data->appointments[i].patientNumber == data->patients[j].patientNumber) {
                    displayScheduleData(&data->patients[j], &data->appointments[i], 0);
                    flag = 0;
                }
            }
        }
    }
    printf("\n");
}

// Add an appointment record to the appointment array
void addAppointment(struct Appointment* app, int maxAppointments, struct Patient* pt, int maxPatients) {
    struct Date date;
    struct Time time;
    int num, index, noTime = 1, noPatient = 1, flag;
    while (noPatient) {
        printf("Patient Number: ");
        num = inputIntPositive();
        index = findPatientIndexByPatientNum(num, pt, maxPatients);
        if (index != -1) {
            noPatient = 0;
            do {
                flag = 1;
                isTimeValid(&date.year, &date.month, &date.day);
                printf("Hour (0-23)  : ");
                time.hour = inputIntRange(0, 23);
                printf("Minute (0-59): ");
                time.min = inputIntRange(0, 59);
                for (int i = 0; i < maxAppointments && flag; i++) {
                    if (date.year == app[i].date.year &&
                        date.month == app[i].date.month &&
                        date.day == app[i].date.day &&
                        time.hour == app[i].time.hour &&
                        time.min == app[i].time.min) {
                        flag = 0;
                        printf("\nERROR: Appointment timeslot is not available!\n\n");
                    }
                }
                if (flag) {
                    while ((time.hour < START_TIME || time.hour > END_TIME) ||
                        (time.hour == END_TIME && time.min > 0) ||
                        (time.min % INTERVAL != 0)) {
                        printf("ERROR: Time must be between %02d:00 and %02d:00 in %02d minute intervals.\n\n",
                            START_TIME, END_TIME, INTERVAL);
                        printf("Hour (0-23)  : ");
                        time.hour = inputIntRange(0, 23);
                        printf("Minute (0-59): ");
                        time.min = inputIntRange(0, 59);
                    }
                    noTime = 0;
                    index = nextAppAvailable(app, maxAppointments);
                    app[index].date = date;
                    app[index].time = time;
                    app[index].patientNumber = num;
                    printf("\n*** Appointment scheduled! ***\n\n");
                }

            } while (noTime);
        }
        else printf("\nERROR: Patient record not found!\n\n");
    }
}

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* app, int maxAppointments, struct Patient* pt, int maxPatients) {
    struct Date date;
    int i, num, index, confirm;
    printf("Patient Number: ");
    num = inputIntPositive();
    index = findPatientIndexByPatientNum(num, pt, maxPatients);
    if (index != -1) {
        isTimeValid(&date.year, &date.month, &date.day);
        int found = 0;
        for (i = 0; i < maxAppointments && found!= 1; i++) {
            if (app[i].patientNumber == num &&
                app[i].date.year == date.year &&
                app[i].date.month == date.month &&
                app[i].date.day == date.day) {
                found = 1;
                printf("\n");
                displayPatientData(&pt[index], FMT_FORM);
                printf("Are you sure you want to remove this appointment (y,n): ");
                confirm = inputCharOption("yn");
                if (confirm == 'y') {
                    app[i].patientNumber = 0;
                    printf("\nAppointment record has been removed!\n\n");
                }
            }
        }

    } else printf("ERROR: Patient record not found!\n\n");
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max) {
    int num, index;
    printf("Search by patient number: ");
    num = inputIntPositive();
    index = findPatientIndexByPatientNum(num, patient, max);
    printf("\n");
    if (index == -1) printf("*** No records found ***\n");
    else displayPatientData(&patient[index], FMT_FORM);
    printf("\n");
}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
    int found = 0;
    char phoneNumber[PHONE_LEN + 1];
    printf("Search by phone number: ");
    inputCString(phoneNumber, 10, 10);
    printf("\n");
    displayPatientTableHeader();
    for (int i = 0; i < max; i++) {
        if (strcmp(phoneNumber, patient[i].phone.number) == 0) {
            displayPatientData(&patient[i], FMT_TABLE);
            found = 1;
        }
    }
    if (!found) printf("\n*** No records found ***\n");
    printf("\n");
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int maxNum = 0;
    for (int i = 0; i < max; i++) {
        if (patient[i].patientNumber > maxNum) maxNum = patient[i].patientNumber;
    }
    return maxNum + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int index = -1, found = 0;
    for (int i = 0; i < max && found != 1; i++) {
        if (patient[i].patientNumber == patientNumber) {
            index = i;
            found = 1;
        }
    }
    return index;
}


//Retrieves the index of the next available appointment,
int nextAppAvailable(struct Appointment* app, int max) {
    int i = 0, found = 0;
    for (i = 0; i < max && found != 1; i++) {
        if (app[i].patientNumber < 1) found = 1;
    }
    return i;
}

//Sort the appointment array in chronological order based on the appointment date and time. 
void sortAppointment(struct Appointment* appoints, int max)
{
    int i;
    struct Appointment temp;
    int flag = 1;

    while (flag) {
        flag = 0;
        for (i = 0; i < max - 1; i++) {
            if (appoints[i].date.year > appoints[i + 1].date.year ||
                (appoints[i].date.year == appoints[i + 1].date.year &&
                    appoints[i].date.month > appoints[i + 1].date.month) ||
                (appoints[i].date.year == appoints[i + 1].date.year &&
                    appoints[i].date.month == appoints[i + 1].date.month &&
                    appoints[i].date.day > appoints[i + 1].date.day) ||
                (appoints[i].date.year == appoints[i + 1].date.year &&
                    appoints[i].date.month == appoints[i + 1].date.month &&
                    appoints[i].date.day == appoints[i + 1].date.day &&
                    appoints[i].time.hour > appoints[i + 1].time.hour) ||
                (appoints[i].date.year == appoints[i + 1].date.year &&
                    appoints[i].date.month == appoints[i + 1].date.month &&
                    appoints[i].date.day == appoints[i + 1].date.day &&
                    appoints[i].time.hour == appoints[i + 1].time.hour &&
                    appoints[i].time.min > appoints[i + 1].time.min)) {
                temp = appoints[i];
                appoints[i] = appoints[i + 1];
                appoints[i + 1] = temp;
                flag = 1;
            }
        }
    }
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient) {
    char patientName[NAME_LEN + 1];
    printf("Patient Data Input\n"
        "------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patientName, 1, NAME_LEN);
    strcpy(patient->name, patientName);
    printf("\n");
    inputPhoneData(&patient->phone);
}


// Get user input for phone contact information
void inputPhoneData(struct Phone* phone) {
    int selection;
    char phoneNumber[PHONE_LEN + 1];
    printf("Phone Information\n"
        "-----------------\n"
        "How will the patient like to be contacted?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: ");
    selection = inputIntRange(1, 4);
    putchar('\n');
    switch (selection) {
    case 1:
        strcpy(phone->description, "CELL");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCStringDigit(phoneNumber, 10);
        strcpy(phone->number, phoneNumber);
        printf("\n");
        break;
    case 2:
        strcpy(phone->description, "HOME");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCStringDigit(phoneNumber, 10);
        strcpy(phone->number, phoneNumber);
        printf("\n");
        break;
    case 3:
        strcpy(phone->description, "WORK");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCStringDigit(phoneNumber, 10);
        strcpy(phone->number, phoneNumber);
        printf("\n");
        break;
    case 4:
        strcpy(phone->description, "TBD");
        phone->number[0] = '\0';
        break;
    }
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int count=0;
    FILE* fp;
    fp = fopen(datafile, "r");
    
    if (fp == NULL) printf("Failed to open file '%s'\n", datafile);
    else {
        while (count < max && !feof(fp)) {
            fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]",
                &patients[count].patientNumber,
                patients[count].name,
                patients[count].phone.description,
                patients[count].phone.number);
            count++;
        }
    }
    fclose(fp);
    return count;
}


// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max) {
    int count = 0;
    FILE* fp;
    fp = fopen(datafile, "r");
    if (fp == NULL) printf("Failed to open file '%s'\n", datafile);
    else {
        while (count < max && !feof(fp)) {
            fscanf(fp, "%d,%d,%d,%d,%d,%d\n",
                &appoints[count].patientNumber,
                &appoints[count].date.year,
                &appoints[count].date.month,
                &appoints[count].date.day,
                &appoints[count].time.hour,
                &appoints[count].time.min);
            count++;
        }
    }
    fclose(fp);
    return count;
}



