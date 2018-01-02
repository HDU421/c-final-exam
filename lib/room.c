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
    // Create error if roomType is invalid
    // and return an invalid result
    if (!validateRoomType(roomType)) {
        printInternalError("Invalid room information", "getRoomInfo");
        room err = {-1};
        return err;
    }

    return roomArr[roomType];
}

bool addRoomInfo(room newInfo) {
    // Create error if room number exceeds
    if (roomTypeCount == MAX_ROOM_NUMBER) {
        printInternalError("Room Number exceeded", "addRoomInfo");
        return false;
    }

    roomArr[roomTypeCount++] = newInfo;
    return true;
}

bool updateRoomInfo(int roomType, room newInfo) {
    if (!validateRoomType(roomType)) {
        printInternalError("Invalid roomType", "updateRoomInfo");
        return false;
    }

    roomArr[roomType] = newInfo;
    return true;
}
