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
    int hourPrice;
    int dayPrice;
    char roomName[MAX_ROOM_NAME_LENGTH];
    bool isAvailable;
} room;

typedef struct _RoomReturn {
    int status;
    room content;
} roomReturn;

int validateRoomType(int roomType);
int validateRoomInfo(room roomInfo);
roomReturn getRoomInfo(int roomType);
int addRoomInfo(room newInfo);
int updateRoomInfo(int roomType, room newInfo);

#endif //C_FINAL_EXAM_ROOM_H

