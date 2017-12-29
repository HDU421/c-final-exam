//
// Created by codgician on 12/22/2017.
//
// This file contains variables and functions
// that are related to room management.
//

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
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
        createError("Invalid room information.");
        return roomArr[0];
    }

    return roomArr[roomType];
}

void addRoomInfo(room newInfo) {

    // Create error if room number exceeds
    if (roomTypeCount == MAX_ROOM_NUMBER) {
        createError("Room Number exceeded!");
        return;
    }

    roomArr[roomTypeCount++] = newInfo;
}

void updateRoomInfo(int roomType, room newInfo) {

    if (!validateRoomType(roomType)) {
        createError("Invalid roomType!");
        return;
    }

    roomArr[roomType] = newInfo;
}
