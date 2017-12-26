#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "customer.h"
#include "misc.h"

/* Returns a trimmed string */

char *trim(char *str) {

    char *result = (char*)malloc(BUFFER_LENGTH + 1);

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

    free(str);
    return result;
}


/* Get user input and return the input as a string */
char *getUserInput() {

    char *buffer = (char*)malloc(BUFFER_LENGTH + 1);

    while (fgets(buffer, BUFFER_LENGTH, stdin)) {

        // Put the pointer at the end of stdin buffer
        fseek (stdin, 0, SEEK_END);

        // Flush stdin if buffer is not empty
        if (ftell(stdin) > 0) {
            printf("Input is too long, please try again...\n");
            flushStdin();
            continue;
        }

        // Trim user input
        buffer = trim(buffer);

        // If input is blank, backspace and await input again
        if (strlen(buffer) == 0) {
            printf("\b\r");
            continue;
        }

        return buffer;
    }
}

/* Room menu */
int roomMenu() {
    printf("\t\tRoom Menu\t\t\n\n\n");
    printf("\t1. Add new room information\n\n");
    printf("\t2. Edit existing room information\n\n");
    printf("\t3. Toggle room availability\n\n");
    printf("\t0. Back...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    // Get user's choice
    unsigned int choice;
    while (sscanf(getUserInput(), "%u", &choice) < 1 || choice > 3) {
        printf("Invalid input, please try again...\n");
    }

    // Guide user to destination menus
    switch (choice) {
        case 1:
            return ADD_ROOM_MENU;
        case 2:
            return EDIT_ROOM_MENU;
        case 3:
            return MARK_ROOM_MENU;
        case 0:
            return MAIN_MENU;
    }

    return ROOM_MENU;
}

int addRoomMenu() {
    printf("\t\tAdd new room\t\t\n\n");

    room newRoomInfo;
    printf("Please enter room name:\n");
    strcpy(newRoomInfo.roomName, getUserInput());

    printf("Please input price (HOURLY/DAILY):\n");
    while (sscanf(getUserInput(), "%u/%u", &newRoomInfo.price[HOUR_PRICE], &newRoomInfo.price[DAY_PRICE]) < 2) {
        printf("\nInvalid room price, please try again...\n");
    }

    if (addRoomInfo(newRoomInfo) == SUCCESS) {
        printf("\nRoom successfully added!\n\n");
    } else {
        printf("\nInternal Error!\n\n");
    }

    printf("\t\tNext step?\t\t\n\n");
    printf("\t1. Add another room\n\n");
    printf("\t0. Back...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    unsigned int choice;
    while (sscanf(getUserInput(), "%u", &choice) < 1 || choice > 1) {
        printf("Invalid input, please try again...\n");
    }

    switch (choice) {
        case 1:
            return ADD_ROOM_MENU;
        case 0:
            return ROOM_MENU;
    }

    return ADD_ROOM_MENU;

}

int editRoomMenu() {
    printf("\t\tEdit existing room\t\t\n\n");

    int typeCount = getRoomTypeCount();
    if (typeCount == 0) {
        printf("No rooms are available, please go back and add some...\n");
        printf("Press ENTER to continue...\n");
        getchar();
        return MAIN_MENU;
    }

    printf("\tExisting rooms:\t\n\n");
    for (int i = 0; i < typeCount; i++) {
        room roomInfo = getRoomInfo(i);
        printf("\t%u. %s - Hourly: %u, Daily: %u, availability: %s\n\n", i + 1, roomInfo.roomName, roomInfo.price[HOUR_PRICE], roomInfo.price[DAY_PRICE], (roomInfo.isAvailable) ? "true" : "false");
    }

    printf("Please select a room type from above to get started:\n");

    unsigned int roomChoice;
    while (sscanf(getUserInput(), "%u", &roomChoice) < 1 || (!validateRoomType(roomChoice - 1) || !getRoomInfo(roomChoice - 1).isAvailable)) {
        if (roomChoice == 0) {
            return ROOM_MENU;
        }
        printf("Room is not available, please try again...\n");
    }

    return EDIT_ROOM_MENU;
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
            printf("\t%u. %s - Hourly: %u, Daily: %u\n\n", i + 1, roomInfo.roomName, roomInfo.price[HOUR_PRICE], roomInfo.price[DAY_PRICE]);
        }
    }

    if (!hasAvailableRoom) {
        printf("No rooms are available, please go back and add some...\n");
        printf("Press ENTER to continue...");
        getchar();
        return MAIN_MENU;
    }

    printf("Please select a room type from above to get started:\n");
    unsigned int roomChoice;
    while (sscanf(getUserInput(), "%u", &roomChoice) < 1 || (!validateRoomType(roomChoice - 1) || !getRoomInfo(roomChoice - 1).isAvailable)) {
        if (roomChoice == 0) {
            return MAIN_MENU;
        }
        printf("Room is not available, please try again...\n");
    }

    return CUSTOMER_MENU;
}

int reportMenu() {
    printf("\t\tFinancial Report Menu\t\t\n\n\n");

    // Prompt for year and month
    printf("Please input year and month with the format of MM/YYYY (Enter 0 to go back):\n");
    unsigned int year, month;
    while (sscanf(getUserInput(), "%2u/%4u", &month, &year) < 2 || year < YEAR_MIN || year > YEAR_MAX || month < MONTH_MIN || month > MONTH_MAX) {
        if (year == 0) {
            return MAIN_MENU;
        }
        printf("Only years between 1970 and 9999 and months between 1 and 12 are supported. Please try again... \n");
    }

    // Retrieve financial report content
    revenue result = getReport(year, month);

    // Print financial report
    clearConsole();

    printf("\t\tFinancial Report of %u/%u\t\t\n\n\n", month, year);
    printf("\tExpected:\t%u\n", result.expected);
    printf("\tReal:\t\t%u\n", result.real);
    printf("\n\n");
    printf("\t\tNext step?\t\t\n\n");
    printf("\t1. Get financial report of another month\n\n");
    printf("\t0. Go back...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    unsigned int choice;
    while (sscanf(getUserInput(), "%u", &choice) < 1 || choice > 1) {
        printf("Invalid input, please try again...\n");
    }

    switch (choice) {
        case 1:
            return REPORT_MENU;
        case 0:
            return MAIN_MENU;
    }

    return REPORT_MENU;
}

int mainMenu() {
    printf("\t\tWelcome to Hotel Manager\t\t\n\n\n");
    printf("\t1. Update room information\n\n");
    printf("\t2. Customer check-in\n\n");
    printf("\t3. View financial report\n\n");
    printf("\t0. Exit...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    unsigned int choice;
    while (sscanf(getUserInput(), "%u", &choice) < 1 || choice > 3) {
        printf("Invalid input, please try again...\n");
    }

    switch (choice) {
        case 1:
            return ROOM_MENU;
        case 2:
            return CUSTOMER_MENU;
        case 3:
            return REPORT_MENU;
        case 0:
            return EXIT_PROGRAM;
    }

    return MAIN_MENU;
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
            case MAIN_MENU:
                menuPt = mainMenu();
                break;
            case ROOM_MENU:
                menuPt = roomMenu();
                break;
            case ADD_ROOM_MENU:
                menuPt = addRoomMenu();
                break;
            case EDIT_ROOM_MENU:
                menuPt = editRoomMenu();
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
