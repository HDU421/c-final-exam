//
// Created by codgician on 12/22/2017.
//

#ifndef C_FINAL_EXAM_ROOM_H
#define C_FINAL_EXAM_ROOM_H

#define MAX_ROOM_NAME_LENGTH 100
#define MAX_ROOM_NUMBER 100
#define HOUR_PRICE 0
#define DAY_PRICE 1

#endif //C_FINAL_EXAM_ROOM_H

#ifndef C_FINAL_EXAM_MACRO_H
#include "macro.h"
#endif //C_FINAL_EXAM_MACRO_H

bool validateRoomType(int roomType);
bool isRoomAvailable(int roomType);
int getRoomTypeCount();
int addNewRoom(int hourPrice, int dayPrice, char *roomName);
int getRoomPrice(int roomType, int priceType);
int updateRoomPrice(int roomType, int priceType, int newPrice);
int updateRoomAvailability(int roomType, bool isAvailable);
