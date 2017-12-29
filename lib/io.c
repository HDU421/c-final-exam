//
// Created by codgi on 12/29/2017.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "error.h"
#include "io.h"
#include "room.h"

#define bool _Bool

/* Clear console (cross platform) */
void clearConsole() {
#if defined _WIN32 || defined _WIN64
    system("cls");
#else
    system("clear");
#endif
}

/* Flushes stdin buffer (failing on Linux with gcc) */
void flushStdin() {
    char ch = 0;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

/* Prints error message */
void printError(int errorType) {
    switch (errorType) {
        case ERR_INPUT_BLANK:
            printf("\b\r");
            break;
        case ERR_INPUT_INVALID:
            printf("Invalid input, please try again...\n");
            break;
        case ERR_INPUT_ROOM_UNAVAILABLE:
            printf("Room unavailable, please try again...\n");
        default:
            return;
    }
}

/* Returns a trimmed string */
char *trim(char *str) {

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

        return buffer;
    }
}

/* Get menu choice */
int getMenuChoice(int lowerLimit, int upperLimit) {
    int choice;

    char *userInput = getUserInput();

    while (sscanf(userInput, "%u", &choice) < 1 || choice < lowerLimit || choice > upperLimit) {
        if (strlen(userInput) == 0) {
            printError(ERR_INPUT_BLANK);
        } else {
            printError(ERR_INPUT_INVALID);
        }
        userInput = getUserInput();
    }

    // Free pointer
    userInput = NULL;
    free(userInput);

    return choice;
}

/* Returns whether any room exists */
bool printRoomChoices(bool hideUnavailable) {
    int typeCount = getRoomTypeCount();

    if (typeCount == 0) {
        printf("No room type exists, please go back and add some...\n");
        return false;
    }

    bool flag = false;
    printf("\tSelectable rooms:\n\n");
    for (int i = 0; i < typeCount; i++) {
        room roomInfo = getRoomInfo(i);
        if (!hideUnavailable || roomInfo.isAvailable) {
            flag = true;
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

    if (hideUnavailable && !flag) {
        printf("All room types are unavailable, please go back and enable some...\n");
        return false;
    }

    return true;
}

/* Get room type choice (need to minus 1 before using) */
int getRoomChoice(bool hideUnavailable) {
    int roomChoice;
    int roomTypeCount = getRoomTypeCount();

    char *userInput = getUserInput();
    while (true) {
        if (sscanf(userInput, "%d", &roomChoice) < 1) {
            if (strlen(userInput)) {
                printError(ERR_INPUT_INVALID);
            } else {
                printError(ERR_INPUT_BLANK);
            }
            continue;
        }
        if (roomChoice == 0) {
            break;
        }
        if (roomChoice < 1 || roomChoice > roomTypeCount) {
            printError(ERR_INPUT_ROOM_UNAVAILABLE);
            continue;
        }
        if (hideUnavailable && !getRoomInfo(roomChoice - 1).isAvailable) {
            printError(ERR_INPUT_ROOM_UNAVAILABLE);
            continue;
        }
        break;
    }

    userInput = NULL;
    free(userInput);

    return roomChoice;
}