# HealthCarePro-Patient-and-Appointment-Management-System

## Overview

HealthCarePro is a C-based application designed to efficiently manage patient records and appointment schedules. This interactive program allows users to add, edit, search, and remove patient data, as well as manage appointment schedules effectively. The data is stored in separate files for persistence and is loaded into memory upon program start.

## Features

- **Patient Management**
  - Add, edit, and remove patient records
  - Search for patients by patient number or phone number
  - Display all patient records in either form or table format

- **Appointment Management**
  - Schedule and remove appointments
  - View all scheduled appointments
  - View appointments for a specific date
  - Sort appointments in chronological order

## File Structure

- **clinic.h**: Header file containing structure definitions, constants, and function prototypes
- **core.h**: Header file containing utility functions for user input and basic interface tasks
- **clinic.c**: Source file implementing patient and appointment management functions
- **core.c**: Source file implementing utility functions
- **main.c**: Source file containing the main function and menu navigation

## How to Use

1. **Compile the Program**: Use a C compiler (e.g., `gcc`) to compile the source code files.
2. **Run the Executable**: Execute the compiled program.
3. **Navigate Menus**: Use the menu options to manage patients and appointments.
4. **Enter Data**: Follow prompts to input and edit patient and appointment data.
5. **View and Search**: Use the view and search functions to display records.

## Installation

1. **Clone the Repository**: 
    ```sh
    git clone https://github.com/most4f4/HealthCarePro-Patient-and-Appointment-Management-System.git
    ```
2. **Navigate to the Project Directory**:
    ```sh
    cd healthcarepro
    ```
3. **Compile the Code**:
    ```sh
    gcc main.c clinic.c core.c -o healthcarepro
    ```
4. **Run the Program**:
    ```sh
    ./healthcarepro
    ```

## Credits

- Developed by Mostafa Hasanalipourshahrabadi
