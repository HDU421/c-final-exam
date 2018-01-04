//
// Created by codgician on 12/29/2017.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "io.h"

/* Clear console (cross-platform) */
void clearConsole() {
#if defined _WIN32 || defined _WIN64
    system("cls");
#else
    system("clear");
#endif
}

/* Pause console: Press ENTER to continue (cross-platform) */
void pauseConsole() {
    printf("Press ENTER to continue...\n");
    getchar();
}

/* Flushes stdin buffer (**failing on Linux with gcc 6) */
void flushStdin() {
    char ch = 0;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

/* Returns a trimmed string, removes spaces at front and end */
char *trim(char *str) {

    // Allocate result
    char *result = (char*)malloc(BUFFER_LENGTH + 1);

    // Remove blank spaces at the head of the string
    int pt = 0;
    while (str[pt] == ' ' || str[pt] == '\t') {
        pt++;
    }
    strncpy(result, str + pt, strlen(str) - pt + 1);

    // Remove blank spaces and '\n' at the end of the string
    pt = strlen(result) - 1;
    while (result[pt] == ' ' || result[pt] == '\t' || result[pt] == '\n') {
        result[pt] = '\0';
    }

    // Free pointer
    str = NULL;
    free(str);

    return result;
}

/* Get user input and return it as a string */
char *getUserInput() {

    // Allocate input buffer
    char *buffer = (char*)malloc(BUFFER_LENGTH + 1);

    while (fgets(buffer, BUFFER_LENGTH, stdin)) {
        #if defined linux
        // Flush stdin if buffer is not empty
        if (!feof(stdin)) {
            printf("Input is too long, please try again...\n");
            flushStdin();
            continue;
        }
        #else
        // Put the pointer at the end of stdin buffer
        fseek (stdin, 0, SEEK_END);
        // Flush stdin if buffer is not empty
        if (ftell(stdin) > 0) {
            printf("Input is too long, please try again...\n");
            flushStdin();
            continue;
        }
        #endif

        // Trim user input
        buffer = trim(buffer);
        return buffer;
    }
}

/* Get menu choice */
int getMenuChoice(int lowerLimit, int upperLimit) {
    int choice;

    char *userInput;

    while (true) {
        userInput = getUserInput();
        if (sscanf(userInput, "%d", &choice) < 1) {
            if (strlen(userInput)) {
                printf("Invalid input, please try again...\n");
            } else {
                printf("\b\r");
            }
            continue;
        }

        if (choice < lowerLimit || choice > upperLimit) {
            printf("Invalid choice, please try again...\n");
            continue;
        }

        break;
    }

    // Free pointer
    userInput = NULL;
    free(userInput);

    return choice;
}

/* Returns whether any room exists */
bool printRoomChoices(bool hideUnavailable) {
    int typeCount = getRoomTypeCount();

    bool hasAvailableRoom = false;
    for (int i = 0; i < typeCount; i++) {
        room roomInfo = getRoomInfo(i);
        if (!hideUnavailable || roomInfo.isAvailable) {
            hasAvailableRoom = true;
            printf("\t%d. \"%s\" - ", i + 1, roomInfo.roomName);
            printf("Hourly: ");
            if (roomInfo.price[HOUR_PRICE]) {
                printf("%u", roomInfo.price[HOUR_PRICE]);
            } else {
                printf("Unavailable");
            }
            printf(", Daily: ");
            if (roomInfo.price[DAY_PRICE]) {
                printf("%u", roomInfo.price[DAY_PRICE]);
            } else {
                printf("Unavailable");
            }
            printf(", Availability: %s\n", roomInfo.isAvailable ? "true" : "false");
        }
    }

    if (typeCount == 0 || (hideUnavailable && !hasAvailableRoom)) {
        printf("\tNo rooms available.\n");
        return false;
    }

    return true;
}

/* Get room type choice (need to minus 1 before using) */
int getRoomChoice(bool hideUnavailable) {
    int roomChoice;
    int roomTypeCount = getRoomTypeCount();

    char *userInput;

    while (true) {
        userInput = getUserInput();
        if (sscanf(userInput, "%d", &roomChoice) < 1) {
            if (strlen(userInput)) {
                printf("Invalid input, please try again...\n");
            } else {
                printf("\b\r");
            }
            continue;
        }
        if (roomChoice == 0) {
            break;
        }
        if (roomChoice < 1 || roomChoice > roomTypeCount) {
            printf("Room unavailable, please try again...\n");
            continue;
        }
        if (hideUnavailable && !getRoomInfo(roomChoice - 1).isAvailable) {
            printf("Room unavailable, please try again...\n");
            continue;
        }
        break;
    }

    userInput = NULL;
    free(userInput);

    return roomChoice;
}

/* List room info */
void printRoomInfo(room roomInfo) {

    printf("\tName: \t\t%s\n", roomInfo.roomName);
    printf("\tPrice:\n");

    printf("\t - Hourly: \t");
    if (roomInfo.price[HOUR_PRICE]) {
        printf("%u", roomInfo.price[HOUR_PRICE]);
    } else {
        printf("Unavailable");
    }
    printf("\n");

    printf("\t - Daily: \t");
    if (roomInfo.price[DAY_PRICE]) {
        printf("%u", roomInfo.price[DAY_PRICE]);
    } else {
        printf("Unavailable");
    }
    printf("\n");
    printf("\n");
}

/* Retrieve datetime user input
 * varNum means number of variables.
 * 2: MM/YYYY
 * 3: MM/DD/YYYY
 * 4: MM/DD/YYYY HH
 * */
datetime getDatetime(int varNum) {
    datetime d;

    if (varNum > 4 || varNum < 2) {
        printInternalError("Invalid varNum", "getDatetime");
        datetime err = {-1};
        return err;
    }

    char *userInput;

    if (varNum == 4) {
        while (true) {
            userInput = getUserInput();
            if (sscanf(userInput, "%2d/%2d/%4d %2d", &d.month, &d.day, &d.year, &d.hour) < varNum) {
                if (strlen(userInput)) {
                    printf("Invalid input, please try again...\n");
                } else {
                    printf("\b\r");
                }
                continue;
            }

            if (d.year < YEAR_MIN || d.year > YEAR_MAX) {
                printf("Invalid year, please try again...\n");
                continue;
            }
            if (d.month < MONTH_MIN || d.month > MONTH_MAX) {
                printf("Invalid month, please try again...\n");
                continue;
            }
            if (d.day < 0 || d.day > getMonthDayCount(d.month, d.year)) {
                printf("Invalid day, please try again...\n");
                continue;
            }
            if (d.hour < 0 || d.hour > HOUR_MAX) {
                printf("Invalid hour, please try again...\n");
                continue;
            }

            break;
        }
    } else if (varNum == 3) {
        while (true) {
            userInput = getUserInput();
            if (sscanf(userInput, "%2d/%2d/%4d", &d.month, &d.day, &d.year) < varNum) {
                if (strlen(userInput)) {
                    printf("Invalid input, please try again...\n");
                } else {
                    printf("\b\r");
                }
                continue;
            }

            if (d.year < YEAR_MIN || d.year > YEAR_MAX) {
                printf("Invalid year, please try again...\n");
                continue;
            }
            if (d.month < MONTH_MIN || d.month > MONTH_MAX) {
                printf("Invalid month, please try again...\n");
                continue;
            }
            if (d.day < 0 || d.day > getMonthDayCount(d.month, d.year)) {
                printf("Invalid day, please try again...\n");
                continue;
            }

            break;
        }
    } else if (varNum == 2) {
        while (true) {
            userInput = getUserInput();
            if (sscanf(userInput, "%2d/%4d", &d.month, &d.year) < varNum) {
                if (strlen(userInput)) {
                    printf("Invalid input, please try again...\n");
                } else {
                    printf("\b\r");
                }
                continue;
            }

            if (d.year < YEAR_MIN || d.year > YEAR_MAX) {
                printf("Invalid year, please try again...\n");
                continue;
            }
            if (d.month < MONTH_MIN || d.month > MONTH_MAX) {
                printf("Invalid month, please try again...\n");
                continue;
            }
            break;
        }
    }

    userInput = NULL;
    free(userInput);

    return d;
}