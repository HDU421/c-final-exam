#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"
#include "misc.h"

char *trim(char *str);
long long int retrieveIntegerInput();
void roomMenu();
void customerMenu();
void reportMenu();
void hiddenMenu();
void mainMenu();

/* Returns a trimmed string. */
char *trim(char *str) {
    char *result;

    // Remove blank spaces at the head of the string
    int pt = 0;
    while (str[pt] == ' ') {
        pt++;
    }
    strncpy(result, str + pt, strlen(str) - pt + 1);

    // Remove blank spaces and '\n' at the end of the string
    pt = strlen(result) - 1;
    while (result[pt] == ' ' || result[pt] == '\n') {
        result[pt] = '\0';
    }

    return result;
}

/* Handle integer input. */
long long int retrieveIntegerInput() {
    // Declare a string as input buffer
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, sizeof(buffer), stdin)) {

        // Flush stdin and prompt for input again
        // if user input exceeds buffer size.
        if (strlen(buffer) == BUFFER_SIZE - 1)
        {
            flushStdin();
            printf("Input is too long, please try again...\n");
            continue;
        }

        // Escape blank spaces
        strcpy(buffer, trim(buffer));

        // If input is blank
        // backspace and await input again
        if (strlen(buffer) == 0)
        {
            printf("\b\r");
            continue;
        }

        // Return the extracted value
        int result;
        sscanf(buffer, "%d", &result);
        return result;
    }
}

/* Prints the room menu. */
void roomMenu() {
    clearConsole();

    printf("\t\tRoom Menu\t\t\n\n\n");
    printf("\t1. Add new room information\n\n");
    printf("\t2. Edit existing room information\n\n");
    printf("\t3. Back...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    // Retrieve input
    int input = retrieveIntegerInput();

    // Keep prompting for input if input is out of range
    while (input < 1 || input > 3) {
        printf("Invalid input, please try again...\n");
        input = retrieveIntegerInput();
    }

    switch (input) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            mainMenu();
            break;
        default:
            roomMenu();
            break;
    }
}

/* Prints the customer menu. */
void customerMenu() {
    clearConsole();
    // To be implemented...

}

/* Prints the financial report menu. */
void reportMenu() {
    clearConsole();
    // To be implemented...
}

/* Some easter eggs here :P */
void hiddenMenu() {
    clearConsole();
    // To be implemented...
}

/* Prints the main menu. */
void mainMenu() {
    clearConsole();

    printf("\t\tWelcome to Hotel Manager\t\t\n\n\n");
    printf("\t1. Update room information\n\n");
    printf("\t2. Customer check-in\n\n");
    printf("\t3. View financial report\n\n");
    printf("\t4. Exit...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    // Retrieve input
    int input = retrieveIntegerInput();

    // Keep prompting for input if input is out of range
    while (input < 1 || input > 4) {
        printf("Invalid input, please try again...\n");
        input = retrieveIntegerInput();
    }

    switch (input) {
        case 1:
            roomMenu();
            break;
        case 2:
            customerMenu();
            break;
        case 3:
            reportMenu();
            break;
        case 4:
            exit(0);
        default:
            mainMenu();
            break;
    }
}

/* Where everything starts :P */
int main(int argc, char *argv[]) {
    mainMenu();
    return 0;
}
