//
// Created by codgician on 12/22/2017.
//
// This file contains variables and functions
// that are related to room management.
//

#include <string.h>

#include "room.h"

typedef struct _Room {
    int hourPrice;
    int dayPrice;
    char roomName[MAX_ROOM_NAME_LENGTH];
    bool isAvailable;
} room;

room roomArr[MAX_ROOM_NUMBER];

int roomTypeCount = 0;

bool validateRoomType(int roomType)
{
    return roomType >= 0 && roomType < roomTypeCount;
}

bool validatePriceType(int priceType)
{
    return priceType == HOUR_PRICE || priceType == DAY_PRICE;
}

bool isRoomAvailable(int roomType)
{
    // Validate roomType
    if (!validateRoomType(roomType))
        return ERROR_INVALID_ROOM_TYPE;

    return roomArr[roomType].isAvailable;
}

int getRoomTypeCount()
{
    return roomTypeCount;
}

int getRoomPrice(int roomType, int priceType)
{
    // Validate roomType
    if (!validateRoomType(roomType))
        return ERROR_INVALID_ROOM_TYPE;

    if (priceType == HOUR_PRICE)
        return roomArr[roomType].hourPrice;
    else if (priceType == DAY_PRICE)
        return roomArr[roomType].dayPrice;
    else
        return ERROR_INVALID_PRICE_TYPE;
}

int addNewRoom(int hourPrice, int dayPrice, char *roomName)
{
    // Validate parameters
    if (hourPrice < 0)
        return ERROR_INVALID_HOUR_PRICE;
    if (dayPrice < 0)
        return ERROR_INVALID_DAY_PRICE;

    roomArr[roomTypeCount].hourPrice = hourPrice;
    roomArr[roomTypeCount].dayPrice = dayPrice;
    strcpy(roomArr[roomTypeCount].roomName, roomName);

    roomTypeCount++;

    // Return roomType
    return roomTypeCount - 1;
}

int updateRoomPrice(int roomType, int priceType, int newPrice)
{
    // Validate roomType
    if (!validateRoomType(roomType))
        return ERROR_INVALID_ROOM_TYPE;

    if (priceType == HOUR_PRICE)
        roomArr[roomType].hourPrice = newPrice;
    else if (priceType == DAY_PRICE)
        roomArr[roomType].dayPrice = newPrice;
    else
        return ERROR_INVALID_PRICE_TYPE;

    return SUCCESS;
}

int updateRoomAvailability(int roomType, bool isAvailable)
{
    // Validate roomType
    if (!validateRoomType(roomType))
        return ERROR_INVALID_ROOM_TYPE;

    roomArr[roomType].isAvailable = isAvailable;

    return SUCCESS;
}
