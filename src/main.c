#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "customer.h"
#include "error.h"
#include "io.h"

#define EXIT_PROGRAM 0
#define MAIN_MENU 1
#define ROOM_MENU 2
#define ADD_ROOM_MENU 3
#define EDIT_ROOM_MENU 4
#define MARK_ROOM_MENU 5
#define CUSTOMER_MENU 6
#define REPORT_MENU 7

/* Room menu */
int roomMenu() {
    printf("\t\tRoom Menu\t\t\n\n\n");
    printf("\t1. Add new room information\n\n");
    printf("\t2. Edit existing room information\n\n");
    printf("\t3. Toggle room availability\n\n");
    printf("\t0. Back...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    int choice = getMenuChoice(0, 3);
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
    newRoomInfo.isAvailable = true;
    printf("Please enter room name (Enter 0 to go back):\n");
    strncpy(newRoomInfo.roomName, getUserInput(), sizeof(newRoomInfo.roomName));

    // Prompt if input is blank
    while (strlen(newRoomInfo.roomName) == 0) {
        printf("\b\r");
        strncpy(newRoomInfo.roomName, getUserInput(), sizeof(newRoomInfo.roomName));
    }

    // Return to room menu if user input is "0"
    if (!strcmp(newRoomInfo.roomName, "0")) {
        return ROOM_MENU;
    }

    printf("Please input price (HOURLY/DAILY, 0 if such type is not available):\n");
    while (sscanf(getUserInput(), "%u/%u", &newRoomInfo.price[HOUR_PRICE], &newRoomInfo.price[DAY_PRICE]) < 2 || (newRoomInfo.price[HOUR_PRICE] == 0 && newRoomInfo.price[DAY_PRICE] == 0)) {
        printf("Invalid room price, please try again...\n");
    }

    addRoomInfo(newRoomInfo);
    clearConsole();
    if (errorStatus) {
        printf("\nFailed to add room...\n\n");
        clearError();
    } else {
        printf("\nRoom successfully added!\n\n");
        printf("\tDetailed Information: \t\n\n");
        printRoomInfo(newRoomInfo);
    }

    printf("\t\tNext step?\t\t\n\n");
    printf("\t1. Add another room\n\n");
    printf("\t0. Back...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    int choice = getMenuChoice(0, 1);
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

    bool result = printRoomChoices(false);
    if (!result) {
        printf("Press ENTER to continue...\n");
        getchar();
        return ROOM_MENU;
    }

    printf("\nPlease select a room type from above to get started:\n");
    int roomChoice = getRoomChoice(false);
    if (roomChoice == 0) {
        return ROOM_MENU;
    }

    clearConsole();
    room roomInfo = getRoomInfo(roomChoice - 1);
    if (errorStatus) {
        printf("Failed to retrieve room information!");
        clearError();
        printf("Press ENTER to continue...\n");
        getchar();
        return MAIN_MENU;
    }

    printf("\t\tEdit room #%u\t\t\n\n", roomChoice);
    printf("\tCurrent information:\n");
    printRoomInfo(roomInfo);

    printf("Please enter new name (leave blank if you want to keep existing name: \n");
    char *tmp = getUserInput();
    if (strlen(tmp) > 0) {
        strncpy(roomInfo.roomName, tmp, sizeof(roomInfo.roomName));
    }

    printf("Please enter new price (HOURLY/DAILY, 0 if such type is not available):\n");
    while (sscanf(getUserInput(), "%u/%u", &roomInfo.price[HOUR_PRICE], &roomInfo.price[DAY_PRICE]) < 2 || (roomInfo.price[HOUR_PRICE] == 0 && roomInfo.price[DAY_PRICE] == 0)) {
        printf("Invalid room price, please try again...\n");
    }

    updateRoomInfo(roomChoice - 1, roomInfo);
    clearConsole();
    if (errorStatus) {
        printf("\nFailed to update room!\n\n");
        clearError();
    } else {
        printf("\nRoom successfully updated!\n\n");
        printf("\tDetailed Information: \t\n\n");
        printRoomInfo(roomInfo);
    }

    printf("\t\tNext step?\t\t\n\n");
    printf("\t1. Edit another room\n\n");
    printf("\t0. Back...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    int choice = getMenuChoice(0, 1);
    switch (choice) {
        case 1:
            return EDIT_ROOM_MENU;
        case 0:
            return ROOM_MENU;
    }

    return EDIT_ROOM_MENU;
}

int markRoomMenu() {
    return MAIN_MENU;
}

int customerMenu() {
    printf("\t\tCustomer Menu\t\t\n\n\n");

    // Print available rooms (hide unavailable ones).
    bool result = printRoomChoices(true);
    if (!result) {
        printf("Press ENTER to continue...\n");
        getchar();
        return MAIN_MENU;
    }

    printf("\nPlease select a room type from above to get started:\n");
    int roomChoice = getRoomChoice(false);
    if (roomChoice == 0) {
        return MAIN_MENU;
    }

    room roomInfo = getRoomInfo(roomChoice - 1);
    if (errorStatus) {
        printf("Failed to retrieve room information!");
        clearError();
        printf("Press ENTER to continue...\n");
        getchar();
        return MAIN_MENU;
    }

    clearConsole();
    printf("\t\tCustomer Menu\t\t\n\n\n");
    printf("\t Selected:\n\n");
    printRoomInfo(roomInfo);
    printf("\tPlease select price type:\n");
    printf("\t1. Hourly\n");
    printf("\t2. Daily\n");
    printf("\t0. Back...\n");
    printf("\nPlease enter your choice to get started:\n");
    int priceType = getMenuChoice(0, 2);
    if (priceType == 0) {
        return CUSTOMER_MENU;
    }
    priceType--;

    datetime startDatetime, endDatetime;
    if (priceType == HOUR_PRICE) {
        printf("Please enter start datetime (MM/DD/YYYY HH):\n");
        startDatetime = getDatetime(true);
        printf("Please enter end datetime (MM/DD/YYYY HH):\n");
        endDatetime = getDatetime(true);
    } else {
        printf("Please enter start date (MM/DD/YYYY):\n");
        startDatetime = getDatetime(false);
        printf("Please enter end date (MM/DD/YYYY):\n");
        endDatetime = getDatetime(false);
    }

    checkIn(roomInfo, priceType, startDatetime, endDatetime);

    printf("\t\tNext step?\t\t\n\n");
    printf("\t1. Check in another customer\n\n");
    printf("\t0. Back...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    int choice = getMenuChoice(0, 1);
    switch (choice) {
        case 1:
            return CUSTOMER_MENU;
        case 0:
            return MAIN_MENU;
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

    int choice = getMenuChoice(0, 1);
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
    printf("\t1. Manage room information\n\n");
    printf("\t2. Customer check-in\n\n");
    printf("\t3. View financial report\n\n");
    printf("\t0. Exit...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    int choice = getMenuChoice(0, 3);
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

/* Acts like a menu selector :P */
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
            case MARK_ROOM_MENU:
                menuPt = markRoomMenu();
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
