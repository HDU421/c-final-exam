#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "customer.h"
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

    // Print room menu
    printf("\t\tRoom Menu\t\t\n\n\n");
    printf("\t1. Show existing rooms\n\n");
    printf("\t2. Add new room information\n\n");
    printf("\t3. Edit existing room information\n\n");
    printf("\t4. Toggle room availability\n\n");
    printf("\t0. Back...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    // Retrieve menu choice
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

/* Print all existing rooms */
int printRoomMenu() {

    printf("\t\tExisting rooms\t\t\n\n");
    printRoomChoices(false);
    printf("\n");
    pauseConsole();
    return ROOM_MENU;
}

/* Add new room */
int addRoomMenu() {
    printf("\t\tAdd new room\t\t\n\n");

    room newRoomInfo;
    newRoomInfo.isAvailable = true;

    // Prompt for room name
    printf("Please enter room name (Enter 0 to go back):\n");
    char *userInput = getUserInput();
    strncpy(newRoomInfo.roomName, userInput, sizeof(newRoomInfo.roomName));

    // Keep prompting if user input is blank
    while (strlen(newRoomInfo.roomName) == 0) {
        printf("\b\r");
        userInput = getUserInput();
        strncpy(newRoomInfo.roomName, userInput, sizeof(newRoomInfo.roomName));
    }

    // Free pointer
    userInput = NULL;
    free(userInput);

    // Return to room menu if user input is "0"
    if (!strcmp(newRoomInfo.roomName, "0")) {
        return ROOM_MENU;
    }

    // Prompt for room price
    printf("Please input price (HOURLY/DAILY, 0 if such type is not available):\n");
    while (sscanf(getUserInput(), "%d/%d", &newRoomInfo.price[HOUR_PRICE], &newRoomInfo.price[DAY_PRICE]) < 2 || (newRoomInfo.price[HOUR_PRICE] == 0 && newRoomInfo.price[DAY_PRICE] == 0)) {
        printf("Invalid room price, please try again...\n");
    }

    // Add room!
    bool result = addRoomInfo(newRoomInfo);
    clearConsole();
    if (result) {
        printf("\nRoom successfully added!\n\n");
        printf("\tDetailed Information: \t\n\n");
        printRoomInfo(newRoomInfo);
    } else {
        printf("\nFailed to add room...\n\n");
    }

    // Next step?
    printf("\t\tNext step?\t\t\n\n");
    printf("\t1. Add another room\n\n");
    printf("\t0. Back...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    // Get menu choice
    int choice = getMenuChoice(0, 1);
    switch (choice) {
        case 1:
            return ADD_ROOM_MENU;
        case 0:
            return ROOM_MENU;
    }

    return ADD_ROOM_MENU;
}

/* Edit existing room info */
int editRoomMenu() {

    printf("\t\tEdit existing room\t\t\n\n");

    // Print all rooms (including unavailable ones)
    bool result = printRoomChoices(false);
    if (!result) {
        printf("\n");
        pauseConsole();
        return ROOM_MENU;
    }

    // Prompt for room choice
    printf("\nPlease select a room type from above to get started:\n");
    int roomChoice = getRoomChoice(false);
    if (roomChoice == 0) {
        return ROOM_MENU;
    }

    // Get room info
    room roomInfo = getRoomInfo(roomChoice - 1);
    if (roomInfo.price[0] < 0) {
        printf("\n");
        printf("Failed to retrieve room information!");
        pauseConsole();
        return MAIN_MENU;
    }

    // Print selected room info
    clearConsole();
    printf("\t\tEdit room #%d\t\t\n\n", roomChoice);
    printf("\tCurrent information:\n");
    printRoomInfo(roomInfo);

    // Prompt for new room name
    printf("Please enter new name (leave it blank if you want to keep existing name: \n");
    char *newRoomName = getUserInput();
    if (strlen(newRoomName) > 0) {
        strncpy(roomInfo.roomName, newRoomName, sizeof(roomInfo.roomName));
    }

    // Free pointer
    newRoomName = NULL;
    free(newRoomName);

    // Prompt for new room price
    printf("Please enter new price (HOURLY/DAILY, 0 if such type is not available):\n");
    while (sscanf(getUserInput(), "%d/%d", &roomInfo.price[HOUR_PRICE], &roomInfo.price[DAY_PRICE]) < 2 || (roomInfo.price[HOUR_PRICE] == 0 && roomInfo.price[DAY_PRICE] == 0)) {
        printf("Invalid room price, please try again...\n");
    }

    // Update room info!
    result = updateRoomInfo(roomChoice - 1, roomInfo);
    clearConsole();
    if (result) {
        printf("\nRoom successfully updated!\n\n");
        printf("\tDetailed Information: \t\n\n");
        printRoomInfo(roomInfo);
    } else {
        printf("\nFailed to update room!\n\n");
    }

    // Next step?
    printf("\t\tNext step?\t\t\n\n");
    printf("\t1. Edit another room\n\n");
    printf("\t0. Back...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    // Get menu choice
    int choice = getMenuChoice(0, 1);
    switch (choice) {
        case 1:
            return EDIT_ROOM_MENU;
        case 0:
            return ROOM_MENU;
    }

    return EDIT_ROOM_MENU;
}

/* Toggle availability of existing room */
int toggleRoomMenu() {
    printf("\t\tChange room availability\t\t\n\n\n");

    // Print all rooms (including unavailable ones)
    bool result = printRoomChoices(false);
    if (!result) {
        printf("\n");
        pauseConsole();
        return ROOM_MENU;
    }

    // Prompt for room choice
    printf("\nPlease select a room type from above to toggle availability:\n");
    int roomChoice = getRoomChoice(false);
    if (roomChoice == 0) {
        return ROOM_MENU;
    }

    // Retrieve room info
    room roomInfo = getRoomInfo(roomChoice - 1);
    if (roomInfo.price[0] < 0) {
        printf("Failed to retrieve room information!");
        pauseConsole();
        return MAIN_MENU;
    }

    // Toggle room availability!
    roomInfo.isAvailable = !roomInfo.isAvailable;
    result = updateRoomInfo(roomChoice - 1, roomInfo);
    clearConsole();
    if (result) {
        printf("\nRoom availability successfully updated!\n\n");
    } else {
        printf("\nFailed to update room availability!\n\n");
    }

    // Next step?
    printf("\t\tNext step?\t\t\n\n");
    printf("\t1. Toggle another room\n\n");
    printf("\t0. Back...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    // Retrieve menu choice
    int choice = getMenuChoice(0, 1);
    switch (choice) {
        case 1:
            return TOGGLE_ROOM_MENU;
        case 0:
            return ROOM_MENU;
    }

    return TOGGLE_ROOM_MENU;
}

/* Check in customers */
int customerMenu() {
    printf("\t\tCustomer Menu\t\t\n\n\n");

    // Print available rooms (hide unavailable ones).
    bool result = printRoomChoices(true);
    if (!result) {
        printf("\n");
        pauseConsole();
        return MAIN_MENU;
    }

    // Prompt for room choices
    printf("\nPlease select a room type from above to get started:\n");
    int roomChoice = getRoomChoice(false);
    if (roomChoice == 0) {
        return MAIN_MENU;
    }

    // Retrieve room info
    room roomInfo = getRoomInfo(roomChoice - 1);
    if (roomInfo.price[0] < 0) {
        printf("Failed to retrieve room information!");
        pauseConsole();
        return MAIN_MENU;
    }

    clearConsole();
    printf("\t\tCustomer Menu\t\t\n\n\n");

    // Print info of currently selected room
    printf("\t Selected:\n\n");
    printRoomInfo(roomInfo);

    int priceType;
    if (roomInfo.price[HOUR_PRICE] == 0) {
        // If room only supports paying by day
        priceType = DAY_PRICE;
        printf("This room only supports paying by day.\n\n");
    } else if (roomInfo.price[DAY_PRICE] == 0) {
        // If room only supports paying by hour
        priceType = HOUR_PRICE;
        printf("This room only supports paying by hour.\n\n");
    } else {
        // Prompt for price type
        printf("\tPlease select price type:\n\n");
        printf("\t1. Hourly\n\n");
        printf("\t2. Daily\n\n");
        printf("\t0. Back...\n\n");
        printf("\n");
        printf("Please enter your choice to get started:\n");

        // Retrieve price type
        priceType = getMenuChoice(0, 2);
        if (priceType == 0) {
            return CUSTOMER_MENU;
        }
        priceType--;
    }

    // Retrieve start and end datetime
    datetime startDatetime, endDatetime;
    int varNum;
    char datetimeFormat[BUFFER_LENGTH + 1];
    if (priceType == HOUR_PRICE) {
        varNum = 4;
        sprintf(datetimeFormat, "MM/DD/YYYY HH");
    } else {
        varNum = 3;
        sprintf(datetimeFormat, "MM/DD/YYYY");
    }

    while (true) {
        printf("Please enter start datetime %s:\n", datetimeFormat);
        startDatetime = getDatetime(varNum);
        if (startDatetime.year == -1) {
            printf("Failed to retrieve start datetime...\n");
            pauseConsole();
            return MAIN_MENU;
        }
        printf("Please enter end datetime %s:\n", datetimeFormat);
        endDatetime = getDatetime(varNum);
        if (endDatetime.year == -1) {
            printf("Failed to retrieve start datetime...\n");
            pauseConsole();
            return MAIN_MENU;
        }
        if (cmpDatetime(startDatetime, endDatetime) == 1) {
            printf("Start datetime can't be bigger than end datetime!\n");
            continue;
        }
        break;
    }

    // Register customer
    checkIn(roomInfo, priceType, startDatetime, endDatetime);

    // Next step?
    printf("\t\tNext step?\t\t\n\n");
    printf("\t1. Check in another customer\n\n");
    printf("\t0. Back...\n\n");
    printf("\n");
    printf("Please select an option to get started:\n");

    // Retrieve menu choice
    int choice = getMenuChoice(0, 1);
    switch (choice) {
        case 1:
            return CUSTOMER_MENU;
        case 0:
            return MAIN_MENU;
    }

    return CUSTOMER_MENU;
}

/* Print financial report of a specific month */
int reportMenu() {
    printf("\t\tFinancial Report Menu\t\t\n\n\n");

    // Prompt for year and month
    printf("Please input year and month with the format of MM/YYYY:\n");
    datetime d;
    d = getDatetime(2);

    // Retrieve financial report content
    revenue result = getReport(d);
    if (result.real < 0 || result.expected < 0) {
        printf("Failed to fetch financial report...\n");
        pauseConsole();
        return MAIN_MENU;
    }

    // Print financial report
    clearConsole();
    printf("\t\tFinancial Report of %02d/%04d\t\t\n\n\n", d.month, d.year);
    printf("\tExpected:\t%d\n", result.expected);
    printf("\tReal:\t\t%d\n", result.real);
    printf("\n\n");

    // Next step?
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

    // Retrieve menu choice
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

    // At entrance it shows main menu
    int menuPt = MAIN_MENU;

    while (menuPt) {
        // First clear all previous output
        clearConsole();

        // Print menu and retrieve next menu
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
