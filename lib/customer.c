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

    if (validatePriceType(priceType) != SUCCESS) {
        result.status = validatePriceType(priceType);
        return result;
    }

    if (duration <= 0) {
        result.status = ERROR_INVALID_DURATION;
        return result;
    }

    result.status = SUCCESS;
    result.content = roomInfo.price[priceType] * duration;

    return result;
}

int checkIn(room roomInfo, int priceType, datetime startDatetime, datetime endDatetime) {
    customerReturn result;

    if (cmpDatetime(startDatetime, endDatetime) == 1) {
        return ERROR_START_DATETIME_LARGER_THAN_END_DATETIME;
    }
    if (validateRoomInfo(roomInfo) != SUCCESS) {
        return  validateRoomInfo(roomInfo);
    }
    if (validatePriceType(priceType) != SUCCESS) {
        return validatePriceType(priceType);
    }

    int cntYear = startDatetime.year - 1970, cntMonth = startDatetime.month - 1;

    // If time period is within current month
    if (startDatetime.year == endDatetime.year && startDatetime.month == endDatetime.month) {

        datetimeReturn duration = getIntervalDays(startDatetime, endDatetime);
        if (duration.status != SUCCESS) {
            return duration.status;
        }

        customerReturn price = getPrice(roomInfo, priceType, duration.content);
        if (price.status != SUCCESS) {
            return price.status;
        }

        revenueArr[cntYear][cntMonth].expected += price.content;
        revenueArr[cntYear][cntMonth].real += price.content;

    } else {

        if (priceType == HOUR_PRICE) {
            customerReturn price = getPrice(roomInfo, priceType, 24 * (getMonthDayCount(startDatetime.month, startDatetime.year) - startDatetime.day + 1) - startDatetime.hour);
            if (price.status != SUCCESS) {
                return price.status;
            }
            revenueArr[cntYear][cntMonth].expected += price.content;
        } else {
            customerReturn price = getPrice(roomInfo, priceType, getMonthDayCount(startDatetime.month, startDatetime.year) - startDatetime.day + 1);
            if (price.status != SUCCESS) {
                return price.status;
            }
            revenueArr[cntYear][cntMonth].expected += price.content;
        }

        while (cntYear < endDatetime.year - 1970 || (cntYear == endDatetime.year - 1970 && cntMonth < endDatetime.month - 2)) {

            if (cntMonth > 11) {
                cntMonth = 0;
                cntYear++;
            } else {
                cntMonth++;
            }

            customerReturn price;

            if (priceType == HOUR_PRICE) {
                price = getPrice(roomInfo, priceType, 24 * getMonthDayCount(cntMonth + 1, cntYear + 1970));
            } else {
                price = getPrice(roomInfo, priceType, getMonthDayCount(cntMonth + 1, cntYear + 1970));
            }

            if (price.status != SUCCESS) {
                return price.status;
            } else {
                revenueArr[cntYear][cntMonth].expected += price.content;
            }
        }

        if (priceType == HOUR_PRICE) {
            customerReturn price = getPrice(roomInfo, priceType, 24 * (endDatetime.day - 1) + endDatetime.hour);
            if (price.status != SUCCESS) {
                return price.status;
            }
            revenueArr[endDatetime.year - 1970][endDatetime.month - 1].expected += price.content;
        } else {
            customerReturn price = getPrice(roomInfo, priceType, endDatetime.day - 1);
            if (price.status != SUCCESS) {
                return price.status;
            }
            revenueArr[endDatetime.year - 1970][endDatetime.month - 1].expected+= price.content;
        }
    }

    return SUCCESS;
}

revenue getReport(int year, int month) {
    return revenueArr[year - 1970][month - 1];
}