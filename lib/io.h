//
// Created by codgician on 12/29/2017.
//

#ifndef C_FINAL_EXAM_INPUT_H
#define C_FINAL_EXAM_INPUT_H

#include "bool.h"
#include "datetime.h"
#include "error.h"
#include "room.h"

#define BUFFER_LENGTH 100

void clearConsole();
void pauseConsole();
void flushStdin();
char *trim(char *str);
char *getUserInput();
int getMenuChoice(int lowerLimit, int upperLimit);
bool printRoomChoices(bool hideUnavailable);
int getRoomChoice(bool hideUnavailable);
void printRoomInfo(room roomInfo);
datetime getDatetime(int varNum);

#endif //C_FINAL_EXAM_INPUT_H
