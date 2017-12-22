//
// Created by codgician on 12/22/2017.
//
// This file contains variables and functions
// that are related to customer management.
//

#include <string.h>
#include <time.h>

#include "macro.h"
#include "room.h"

typedef struct _Revenue {
    int expected;
    int real;
} revenue;

revenue revenueArr[YEAR_COUNT][MONTH_COUNT];

long long int moneySum = 0;

void initProfitArr()
{
    for (int i = 0; i < YEAR_COUNT; i++)
    {
        for (int j = 0; j < MONTH_COUNT; j++)
        {
            revenueArr[i][j].expected = 0;
            revenueArr[i][j].real = 0;
        }
    }
}

int getPrice(int roomType, int priceType, int duration)
{
    // Validate parameters
    if (!validateRoomType(roomType))
        return ERROR_INVALID_ROOM_TYPE;
    if (!validatePriceType(priceType))
        return ERROR_INVALID_PRICE_TYPE;
    if (duration <= 0)
        return ERROR_INVALID_DURATION;

    int roomPrice = getRoomPrice(roomType, priceType);

    // If error occurred (though quite impossible), return error code
    if (roomPrice < 0)
        return roomPrice;

    return roomPrice * duration;
}
