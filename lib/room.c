//
// Created by codgician on 12/22/2017.
//
// This file contains variables and functions
// that are related to room management.
//

#include "room.h"

room roomArr[MAX_ROOM_NUMBER];

int roomTypeCount = 0;

int getRoomTypeCount() {
    return roomTypeCount;
}

bool validateRoomType(int roomType) {
    if (roomType < 0 || roomType >= roomTypeCount) {
        return false;
    }
    return true;
}

bool validatePriceType(int priceType) {
    if (priceType != HOUR_PRICE && priceType != DAY_PRICE) {
        return false;
    }
    return true;
}

room getRoomInfo(int roomType) {

    if (validateRoomType(roomType) != SUCCESS) {
        // result.status = ERROR_INVALID_ROOM_TYPE;
    } else {
        // result.status = SUCCESS;
        // result.content = roomArr[roomType];
    }

    return roomArr[roomType];
}

int addRoomInfo(room newInfo) {
    roomArr[roomTypeCount++] = newInfo;

    return SUCCESS;
}

int updateRoomInfo(int roomType, room newInfo) {

    if (!validateRoomType(roomType)) {
        return ERROR_INVALID_ROOM_TYPE;
    }

    roomArr[roomType] = newInfo;

    return SUCCESS;
}
