//
// Created by codgician on 12/29/2017.
//

#ifndef C_FINAL_EXAM_INPUT_H
#define C_FINAL_EXAM_INPUT_H

#define BUFFER_LENGTH 100

#define ERR_INPUT_BLANK 1
#define ERR_INPUT_INVALID 2
#define ERR_INPUT_ROOM_UNAVAILABLE 3

#include "bool.h"
#include "datetime.h"
#include "room.h"

void clearConsole();
void flushStdin();
char *trim(char *str);
char *getUserInput();
int getMenuChoice(int lowerLimit, int upprLimit);
bool printRoomChoices(bool hideUnavailable);
int getRoomChoice(bool hideUnavailable);
void printRoomInfo(room roomInfo);
datetime getDatetime(bool getHour);

#endif //C_FINAL_EXAM_INPUT_H
