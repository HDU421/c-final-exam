//
// Created by codgician on 12/22/2017.
//

#ifndef C_FINAL_EXAM_MACRO_H
#include "macro.h"
#endif //C_FINAL_EXAM_MACRO_H

#ifndef C_FINAL_EXAM_ROOM_H
#define C_FINAL_EXAM_ROOM_H

#define MAX_ROOM_NAME_LENGTH 100
#define MAX_ROOM_NUMBER 100
#define HOUR_PRICE 0
#define DAY_PRICE 1

typedef struct _Room {
    int price[2];
    char roomName[MAX_ROOM_NAME_LENGTH];
    bool isAvailable;
} room;

int validateRoomType(int roomType);
int validatePriceType(int priceType);
int validateRoomInfo(room roomInfo);
room getRoomInfo(int roomType);
int addRoomInfo(room newInfo);
int updateRoomInfo(int roomType, room newInfo);

#endif //C_FINAL_EXAM_ROOM_H
