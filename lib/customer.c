//
// Created by codgician on 12/22/2017.
//
// This file contains variables and functions
// that are related to customer management.
//

#include "customer.h"

revenue revenueArr[YEAR_COUNT][MONTH_COUNT];

long long int moneySum = 0;

void initRevenueArr() {
    for (int i = 0; i < YEAR_COUNT; i++) {
        for (int j = 0; j < MONTH_COUNT; j++) {
            revenueArr[i][j].expected = 0;
            revenueArr[i][j].real = 0;
        }
    }
}

customerReturn getPrice(room roomInfo, int priceType, int duration) {
    customerReturn result;

    if (validateRoomInfo(roomInfo) != SUCCESS) {
        result.status =  validateRoomInfo(roomInfo);
        return result;
    }

    if (duration <= 0) {
        result.status = ERROR_INVALID_DURATION;
        return result;
    }

    if (priceType == HOUR_PRICE) {
        result.status = SUCCESS;
        result.content = roomInfo.hourPrice * duration;
    } else if (priceType == DAY_PRICE) {
        result.status = SUCCESS;
        result.content = roomInfo.dayPrice * duration;
    } else {
        result.status = ERROR_INVALID_PRICE_TYPE;
    }

    return result;
}

// Unfinished!
int checkIn(room roomInfo, datetime startDatetime, datetime endDatetime) {
    customerReturn result;

    if (validateRoomInfo(roomInfo) != SUCCESS) {
        return  validateRoomInfo(roomInfo);
    }

    return SUCCESS;
}
