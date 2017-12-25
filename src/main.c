#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "customer.h"
#include "macro.h"
#include "misc.h"


/* Returns a trimmed string */
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

/* Handle integer input */
long long int retrieveIntegerInput() {
    // Declare a string as input buffer
    char buffer[BUFFER_LENGTH];

    while (fgets(buffer, sizeof(buffer), stdin)) {

        // Flush stdin and prompt for input again
        // if user input exceeds buffer size.
        if (strlen(buffer) == BUFFER_LENGTH - 1) {
            flushStdin();
            printf("Input is too long, please try again...\n");
            continue;
        }

        // Escape blank spaces
        strcpy(buffer, trim(buffer));

        // If input is blank, backspace and await input again
        if (strlen(buffer) == 0) {
            printf("\b\r");
            continue;
        }

        // Ensure that the retrieved value is smaller than int32.
        if (strlen(buffer) > INT32_LENGTH) {
            printf("Input value is too big, please try again...\n");
            continue;
        }

        // Validate if user input is an integer
        bool isNumber = true;
        for (int i = 0; i < strlen(buffer); i++) {
            if (!isdigit(buffer[i])) {
                isNumber = false;
                break;
            }
        }
        if (!isNumber) {
            printf("Input should only contain digits, please try again...\n");
            continue;
        }

        // Return the extracted value
        int result;
        sscanf(buffer, "%d", &result);
        return result;
    }
}

/* Functions below prints the according menu
 * and returns the next menu */
int roomMenu() {

    printf("\t\tRoom Menu\t\t\n\n\n");
    printf("\t1. Add new room information\n\n");
    printf("\t2. Edit existing room information\n\n");
    printf("\t3. Back...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    int choice = retrieveIntegerInput();
    while (choice < 0 || choice > 3) {
        choice = retrieveIntegerInput();
    }

    switch (choice) {
        case 1:
            return 5;
        case 2:
            return 6;
        case 3:
            return 1;
    }

    return 2;
}

int reportMenu() {
    // To be implemented
    return 1;
}

int mainMenu() {
    printf("\t\tWelcome to Hotel Manager\t\t\n\n\n");
    printf("\t1. Update room information\n\n");
    printf("\t2. Customer check-in\n\n");
    printf("\t3. View financial report\n\n");
    printf("\t4. Exit...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    int choice = retrieveIntegerInput();
    while (choice < 0 || choice > 4) {
        choice = retrieveIntegerInput();
    }

    switch (choice) {
        case 1:
            return 2;
        case 2:
            return 3;
        case 3:
            return 4;
        case 4:
            return 0;
    }

    return 1;
}

/* Where everything starts :P */
int main(int argc, char *argv[]) {

    // Some initialization work
    initRevenueArr();

    int menuPt = 1;
    while (menuPt) {
        // First clear all previous output
        clearConsole();

        // Current menu
        switch (menuPt) {
            case 1:
                menuPt = mainMenu();
                break;
            case 2:
                menuPt = roomMenu();
                break;
            case 3:
                menuPt = reportMenu();
                break;
        }
    }
    return 0;
}
