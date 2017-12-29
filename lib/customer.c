//
// Created by codgician on 12/22/2017.
//
// This file contains variables and functions
// that are related to customer management.
//

#include "customer.h"
#include "error.h"

// struct "revenue" is defined in "customer.h"
revenue revenueArr[YEAR_COUNT][MONTH_COUNT];

/* Initialize revenue array */
void initRevenueArr() {
    for (int i = 0; i < YEAR_COUNT; i++) {
        for (int j = 0; j < MONTH_COUNT; j++) {
            revenueArr[i][j].expected = 0;
            revenueArr[i][j].real = 0;
        }
    }
}

/* Calculate total price for a specific check-in */
long long int getPrice(room roomInfo, int priceType, long long int duration) {

    if (!validatePriceType(priceType)) {
        createError("Invalid price type!");
        return -1;
    }

    if (duration <= 0) {
        createError("Invalid duration!");
        return -1;
    }

    return roomInfo.price[priceType] * duration;
}

/* Check in and update revenue */
void checkIn(room roomInfo, int priceType, datetime startDatetime, datetime endDatetime) {

    if (cmpDatetime(startDatetime, endDatetime) == 1) {
        createError("End datetime smaller than start datetime.");
        return;
    }

    if (!validatePriceType(priceType)) {
        createError("Invalid priceType.");
        return;
    }

    int cntYear = startDatetime.year - 1970, cntMonth = startDatetime.month - 1;

    // If time period is within current month
    if (startDatetime.year == endDatetime.year && startDatetime.month == endDatetime.month) {

        long long int duration = getIntervalDays(startDatetime, endDatetime);
        int price = getPrice(roomInfo, priceType, duration);

        revenueArr[cntYear][cntMonth].expected += price;
        revenueArr[cntYear][cntMonth].real += price;

    } else {

        if (priceType == HOUR_PRICE) {
            int price = getPrice(roomInfo, priceType, 24 * (getMonthDayCount(startDatetime.month, startDatetime.year) - startDatetime.day + 1) - startDatetime.hour);
            revenueArr[cntYear][cntMonth].expected += price;
        } else {
            int price = getPrice(roomInfo, priceType, getMonthDayCount(startDatetime.month, startDatetime.year) - startDatetime.day + 1);
            revenueArr[cntYear][cntMonth].expected += price;
        }

        while (cntYear < endDatetime.year - 1970 || (cntYear == endDatetime.year - 1970 && cntMonth < endDatetime.month - 2)) {

            if (cntMonth > 11) {
                cntMonth = 0;
                cntYear++;
            } else {
                cntMonth++;
            }

            int price;

            if (priceType == HOUR_PRICE) {
                price = getPrice(roomInfo, priceType, 24 * getMonthDayCount(cntMonth + 1, cntYear + 1970));
            } else {
                price = getPrice(roomInfo, priceType, getMonthDayCount(cntMonth + 1, cntYear + 1970));
            }

            revenueArr[cntYear][cntMonth].expected += price;

        }

        if (priceType == HOUR_PRICE) {
            int price = getPrice(roomInfo, priceType, 24 * (endDatetime.day - 1) + endDatetime.hour);
            revenueArr[endDatetime.year - 1970][endDatetime.month - 1].expected += price;
        } else {
            int price = getPrice(roomInfo, priceType, endDatetime.day - 1);
            revenueArr[endDatetime.year - 1970][endDatetime.month - 1].expected+= price;
        }
    }
}

/* Return financial report for a specific month */
revenue getReport(int year, int month) {

    if (year < YEAR_MIN || year > YEAR_MAX) {
        createError("Invalid year!");
        return revenueArr[0][0];
    }

    if (month < MONTH_MIN || month > MONTH_MAX) {
        createError("Invalid month!");
        return revenueArr[0][0];
    }

    return revenueArr[year - 1970][month - 1];
}