#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "customer.h"
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
 * and return the id of the next menu */
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
            break;
        case 2:
            break;
        case 3:
            return MAIN_MENU;
    }

    return 2;
}

int customerMenu() {
    printf("\t\tCustomer Menu\t\t\n\n\n");

    int typeCount = getRoomTypeCount();

    bool hasAvailableRoom = false;
    for (int i = 0; i < typeCount; i++) {

        room roomInfo = getRoomInfo(i);
        if (roomInfo.isAvailable) {
            if (!hasAvailableRoom) {
                printf("\tAvailable room choices:\t\n\n");
                hasAvailableRoom = true;
            }
            printf("\t%d. %s - Hourly: %d, Daily: %d\n\n", i + 1, roomInfo.roomName, roomInfo.price[HOUR_PRICE], roomInfo.price[DAY_PRICE]);
        }
    }

    if (!hasAvailableRoom) {
        printf("No rooms are available, please go back and add some...\n");
        printf("Press ENTER to continue...");
        getchar();
        return 1;
    }

    printf("Please select a room type from above to get started:\n");
    int roomChoice = retrieveIntegerInput();
    while (!validateRoomType(roomChoice) || !getRoomInfo(roomChoice).isAvailable) {
        printf("Invalid choice, please try again...\n");
        roomChoice = retrieveIntegerInput();
    }

    return 1;
}

int reportMenu() {
    printf("\t\tFinancial Report Menu\t\t\n\n\n");
    printf("Please enter year (Enter 0 to go back):\n");

    int year = retrieveIntegerInput();
    while (year < YEAR_MIN || year > YEAR_MAX) {
        if (year == 0) {
            return 1;
        }
        printf("Only years between 1970 and 9999 are supported. Please try again... \n");
        year = retrieveIntegerInput();
    }

    printf("Please enter month (Enter 0 to go back):\n");
    int month = retrieveIntegerInput();
    while (month < MONTH_MIN || month > MONTH_MAX) {
        if (month == 0) {
            return 1;
        }
        printf("Only months between 1 and 12 are supported. Please try again... \n");
        month = retrieveIntegerInput();
    }

    // Retrieve financial report content
    revenue result = getReport(year, month);

    clearConsole();

    printf("\t\tFinancial Report of %d/%d\t\t\n\n\n", month, year);
    printf("\tExpected:\t%d\n", result.expected);
    printf("\tReal:\t\t%d\n", result.real);
    printf("\n\n");
    printf("\tNext step?\n\n");
    printf("\t1. Get financial report of another month\n\n");
    printf("\t2. Go back...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    int choice = retrieveIntegerInput();
    while (choice < 0 || choice > 2) {
        choice = retrieveIntegerInput();
    }

    switch (choice) {
        case 1:
            return REPORT_MENU;
        case 2:
            return MAIN_MENU;
    }

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
            return ROOM_MENU;
        case 2:
            return CUSTOMER_MENU;
        case 3:
            return REPORT_MENU;
        case 4:
            return EXIT_PROGRAM;
    }

    return 1;
}

/* Where everything starts :P */
int main(int argc, char *argv[]) {

    // Some initialization work
    initRevenueArr();
    room test;
    test.isAvailable = true;
    test.price[HOUR_PRICE] = 10;
    test.price[DAY_PRICE] = 100;
    strcpy(test.roomName, "TEST");
    addRoomInfo(test);

    int menuPt = 1;
    while (menuPt) {
        // First clear all previous output
        clearConsole();

        // Current menu
        switch (menuPt) {
            case MAIN_MENU:
                menuPt = mainMenu();
                break;
            case ROOM_MENU:
                menuPt = roomMenu();
                break;
            case CUSTOMER_MENU:
                menuPt = customerMenu();
                break;
            case REPORT_MENU:
                menuPt = reportMenu();
                break;
            default:
                menuPt = MAIN_MENU;
                break;
        }
    }
    return 0;
}
