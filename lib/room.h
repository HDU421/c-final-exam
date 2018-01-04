//
// Created by AlphaMing on 12/22/2017.
//

#ifndef C_FINAL_EXAM_ROOM_H
#define C_FINAL_EXAM_ROOM_H

#define MAX_ROOM_NAME_LENGTH 10010      // Maximum length of room name
#define MAX_ROOM_NUMBER 10010           // Maximum number of room types
#define HOUR_PRICE 0
#define DAY_PRICE 1

#include "bool.h"
#include "error.h"

typedef struct _Room {
    int price[2];
    char roomName[MAX_ROOM_NAME_LENGTH + 1];
    bool isAvailable;
} room;

int getRoomTypeCount();
bool validateRoomType(int roomType);
bool validatePriceType(int priceType);
bool validateRoomInfo(room roomInfo);
room getRoomInfo(int roomType);
bool addRoomInfo(room newInfo);
bool updateRoomInfo(int roomType, room newInfo);

#endif //C_FINAL_EXAM_ROOM_H
