//
// Created by codgician on 12/22/2017.
//
// This file contains variables and functions
// that are related to room management.
//

#include "room.h"

room roomArr[MAX_ROOM_NUMBER];

int roomTypeCount = 0;

int validateRoomType(int roomType) {
    if (roomType < 0 || roomType >= roomTypeCount) {
        return ERROR_INVALID_ROOM_TYPE;
    }
    return SUCCESS;
}

int validateRoomInfo(room roomInfo) {

    if (roomInfo.hourPrice <= 0) {
        return ERROR_INVALID_HOUR_PRICE;
    }

    if (roomInfo.dayPrice <= 0) {
        return ERROR_INVALID_DAY_PRICE;
    }

    return SUCCESS;
}

roomReturn getRoomInfo(int roomType) {
    roomReturn result;

    if (validateRoomType(roomType) != SUCCESS) {
        result.status = ERROR_INVALID_ROOM_TYPE;
    } else {
        result.status = SUCCESS;
        result.content = roomArr[roomType];
    }

    return result;
}

int addRoomInfo(room newInfo) {

    if (validateRoomInfo(newInfo) != SUCCESS) {
        return validateRoomInfo(newInfo);
    }

    roomArr[roomTypeCount++] = newInfo;

    return SUCCESS;
}

int updateRoomInfo(int roomType, room newInfo) {

    if (validateRoomInfo(newInfo) != SUCCESS) {
        return validateRoomInfo(newInfo);
    }

    if (!validateRoomType(roomType)) {
        return ERROR_INVALID_ROOM_TYPE;
    }

    roomArr[roomType] = newInfo;

    return SUCCESS;
}
