#include <stdio.h>
#include <string.h>

#include "customer.h"
#include "error.h"
#include "io.h"

#define EXIT_PROGRAM 0
#define MAIN_MENU 1
#define ROOM_MENU 2
#define PRINT_ROOM_MENU 3
#define ADD_ROOM_MENU 4
#define EDIT_ROOM_MENU 5
#define TOGGLE_ROOM_MENU 6
#define CUSTOMER_MENU 7
#define REPORT_MENU 8

/* Room menu */
int roomMenu() {
    printf("\t\tRoom Menu\t\t\n\n\n");
    printf("\t1. Show existing rooms\n\n");
    printf("\t2. Add new room information\n\n");
    printf("\t3. Edit existing room information\n\n");
    printf("\t4. Toggle room availability\n\n");
    printf("\t0. Back...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    int choice = getMenuChoice(0, 4);
    switch (choice) {
        case 1:
            return PRINT_ROOM_MENU;
        case 2:
            return ADD_ROOM_MENU;
        case 3:
            return EDIT_ROOM_MENU;
        case 4:
            return TOGGLE_ROOM_MENU;
        case 0:
            return MAIN_MENU;
    }

    return ROOM_MENU;
}

int printRoomMenu() {
    printf("\t\tExisting rooms\t\t\n\n");
    printRoomChoices(false);
    printf("\n");
    printf("Press ENTER to continue...");
    getchar();
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

    bool result = addRoomInfo(newRoomInfo);
    clearConsole();
    if (result) {
        printf("\nRoom successfully added!\n\n");
        printf("\tDetailed Information: \t\n\n");
        printRoomInfo(newRoomInfo);
    } else {
        printf("\nFailed to add room...\n\n");
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
    if (roomInfo.price[0] < 0) {
        printf("Failed to retrieve room information!");
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

    result = updateRoomInfo(roomChoice - 1, roomInfo);
    clearConsole();
    if (result) {
        printf("\nRoom successfully updated!\n\n");
        printf("\tDetailed Information: \t\n\n");
        printRoomInfo(roomInfo);
    } else {
        printf("\nFailed to update room!\n\n");
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

int toggleRoomMenu() {
    printf("\t\tChange room availability\t\t\n\n\n");

    bool result = printRoomChoices(false);
    if (!result) {
        printf("Press ENTER to continue...\n");
        getchar();
        return ROOM_MENU;
    }

    printf("\nPlease select a room type from above to toggle availability:\n");
    int roomChoice = getRoomChoice(false);
    if (roomChoice == 0) {
        return ROOM_MENU;
    }

    room roomInfo = getRoomInfo(roomChoice - 1);
    if (roomInfo.price[0] < 0) {
        printf("Failed to retrieve room information!");
        printf("Press ENTER to continue...\n");
        getchar();
        return MAIN_MENU;
    }

    roomInfo.isAvailable = !roomInfo.isAvailable;

    result = updateRoomInfo(roomChoice - 1, roomInfo);
    clearConsole();
    if (result) {
        printf("\nRoom availability successfully updated!\n\n");
    } else {
        printf("\nFailed to update room availability!\n\n");
    }

    printf("\t\tNext step?\t\t\n\n");
    printf("\t1. Toggle another room\n\n");
    printf("\t0. Back...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    int choice = getMenuChoice(0, 1);
    switch (choice) {
        case 1:
            return TOGGLE_ROOM_MENU;
        case 0:
            return ROOM_MENU;
    }

    return TOGGLE_ROOM_MENU;
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
    if (roomInfo.price[0] < 0) {
        printf("Failed to retrieve room information!");
        printf("Press ENTER to continue...\n");
        getchar();
        return MAIN_MENU;
    }

    clearConsole();
    printf("\t\tCustomer Menu\t\t\n\n\n");
    printf("\t Selected:\n\n");
    printRoomInfo(roomInfo);
    printf("\tPlease select price type:\n\n");
    printf("\t1. Hourly\n\n");
    printf("\t2. Daily\n\n");
    printf("\t0. Back...\n\n");
    printf("\n");
    printf("Please enter your choice to get started:\n");
    int priceType = getMenuChoice(0, 2);
    if (priceType == 0) {
        return CUSTOMER_MENU;
    }
    priceType--;

    datetime startDatetime, endDatetime;
    if (priceType == HOUR_PRICE) {

        while (true) {
            printf("Please enter start datetime (MM/DD/YYYY HH):\n");
            startDatetime = getDatetime(true);
            printf("Please enter end datetime (MM/DD/YYYY HH):\n");
            endDatetime = getDatetime(true);
            if (cmpDatetime(startDatetime, endDatetime) == 1) {
                printf("Start datetime can't be bigger than end datetime!\n");
                continue;
            }
            break;
        }
    } else {
        while (true) {
            printf("Please enter start date (MM/DD/YYYY):\n");
            startDatetime = getDatetime(false);
            printf("Please enter end date (MM/DD/YYYY):\n");
            endDatetime = getDatetime(false);
            if (cmpDatetime(startDatetime, endDatetime) == 1) {
                printf("Start datetime can't be bigger than end datetime!\n");
                continue;
            }
            break;
        }
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
    if (result.real < 0 || result.expected < 0) {
        printf("Failed to fetch financial report...\n");
        printf("Press ENTER to continue...\n");
        getchar();
        return MAIN_MENU;
    }

    // Print financial report
    clearConsole();

    printf("\t\tFinancial Report of %02u/%04u\t\t\n\n\n", month, year);
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
            case PRINT_ROOM_MENU:
                menuPt = printRoomMenu();
                break;
            case ADD_ROOM_MENU:
                menuPt = addRoomMenu();
                break;
            case EDIT_ROOM_MENU:
                menuPt = editRoomMenu();
                break;
            case TOGGLE_ROOM_MENU:
                menuPt = toggleRoomMenu();
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
