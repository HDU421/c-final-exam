//
// Created by AlphaMing on 12/22/2017.
//
// This file contains variables and functions
// that are related to room management.
//

#include <string.h>

#include "room.h"

room roomArr[MAX_ROOM_NUMBER];
int roomTypeCount = 0;

/* Retrieves number of available room types */
int getRoomTypeCount() {
    return roomTypeCount;
}

/* Validate given room type id */
bool validateRoomType(int roomType) {
    return roomType >= 0 && roomType < roomTypeCount;
}

/* Validate given price type */
bool validatePriceType(int priceType) {
    return priceType == HOUR_PRICE || priceType == DAY_PRICE;
}

/* Validate given room info */
bool validateRoomInfo(room roomInfo) {
    return strlen(roomInfo.roomName) > 0
           && roomInfo.price[HOUR_PRICE] >= 0
           && roomInfo.price[DAY_PRICE] >= 0
           && !(roomInfo.price[HOUR_PRICE] == 0 && roomInfo.price[DAY_PRICE] == 0);
}

/* Retrieve room info */
room getRoomInfo(int roomType) {
    // Return error if room type is invalid
    if (!validateRoomType(roomType)) {
        printInternalError("Invalid room information", "getRoomInfo");
        room err = {-1};
        return err;
    }

    return roomArr[roomType];
}

/* Add new room info */
bool addRoomInfo(room newInfo) {
    // Return error if room number exceeds
    if (roomTypeCount == MAX_ROOM_NUMBER) {
        printInternalError("Room Number exceeded", "addRoomInfo");
        return false;
    }

    // Return error if room info is invalid
    if (validateRoomInfo(newInfo)) {
        printInternalError("Invalid room info", "addRoomInfo");
        return false;
    }

    roomArr[roomTypeCount++] = newInfo;
    return true;
}

/* Update existing room info */
bool updateRoomInfo(int roomType, room newInfo) {
    // Return error if given room type is invalid
    if (!validateRoomType(roomType)) {
        printInternalError("Invalid room type", "updateRoomInfo");
        return false;
    }

    // Return error if room info is invalid
    if (validateRoomInfo(newInfo)) {
        printInternalError("Invalid room info", "updateRoomInfo");
        return false;
    }

    roomArr[roomType] = newInfo;
    return true;
}
