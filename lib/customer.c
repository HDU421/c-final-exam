//
// Created by codgician on 12/22/2017.
//
// This file contains variables and functions
// that are related to customer management.
//

#include "customer.h"

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
        printInternalError("Invalid price type!");
        return -1;
    }

    if (duration <= 0) {
        printInternalError("Invalid duration!");
        return -1;
    }

    return roomInfo.price[priceType] * duration;
}

/* Check in and update revenue */
bool checkIn(room roomInfo, int priceType, datetime startDatetime, datetime endDatetime) {

    unsigned int checkOption;
    if (priceType == DAY_PRICE) {
        checkOption = CHECK_YEAR + CHECK_MONTH + CHECK_DAY;
    } else if (priceType == HOUR_PRICE) {
        checkOption = CHECK_YEAR + CHECK_MONTH + CHECK_DAY + CHECK_HOUR;
    } else {
        printInternalError("Invalid price type.");
        return false;
    }

    if (cmpDatetime(startDatetime, endDatetime, checkOption) == 1) {
        printInternalError("End datetime smaller than start datetime.");
        return false;
    }

    int cntYear = startDatetime.year - 1970, cntMonth = startDatetime.month - 1;
    long long int price = 0;

    // If time period is within current month
    if (startDatetime.year == endDatetime.year && startDatetime.month == endDatetime.month) {

        if (priceType == HOUR_PRICE) {
            price = getPrice(roomInfo, priceType, getIntervalHours(startDatetime, endDatetime));
        } else {
            price = getPrice(roomInfo, priceType, getIntervalDays(startDatetime, endDatetime));
        }
        revenueArr[cntYear][cntMonth].expected += price;
        revenueArr[cntYear][cntMonth].real += price;

    } else {

        long long int priceSum = 0;

        if (priceType == HOUR_PRICE) {
            price = getPrice(roomInfo, priceType, 24 * (getMonthDayCount(startDatetime.month, startDatetime.year) - startDatetime.day + 1) - startDatetime.hour);
        } else {
            price = getPrice(roomInfo, priceType, getMonthDayCount(startDatetime.month, startDatetime.year) - startDatetime.day + 1);
        }
        revenueArr[cntYear][cntMonth].expected += price;
        priceSum += price;

        while (cntYear < endDatetime.year - 1970 || (cntYear == endDatetime.year - 1970 && cntMonth < endDatetime.month - 2)) {

            if (cntMonth > 11) {
                cntMonth = 0;
                cntYear++;
            } else {
                cntMonth++;
            }

            if (priceType == HOUR_PRICE) {
                price = getPrice(roomInfo, priceType, 24 * getMonthDayCount(cntMonth + 1, cntYear + 1970));
            } else {
                price = getPrice(roomInfo, priceType, getMonthDayCount(cntMonth + 1, cntYear + 1970));
            }

            revenueArr[cntYear][cntMonth].expected += price;
            priceSum += price;

        }

        if (priceType == HOUR_PRICE) {
            price = getPrice(roomInfo, priceType, 24 * (endDatetime.day - 1) + endDatetime.hour);
        } else {
            price = getPrice(roomInfo, priceType, endDatetime.day - 1);
        }
        revenueArr[endDatetime.year - 1970][endDatetime.month - 1].expected += price;
        priceSum += price;

        revenueArr[endDatetime.year - 1970][endDatetime.month - 1].real += priceSum;
    }

    return true;
}

/* Return financial report for a specific month */
revenue getReport(datetime d) {

    if (d.year < YEAR_MIN || d.year > YEAR_MAX) {
        printInternalError("Invalid year!");
        revenue err = {-1};
        return err;
    }

    if (d.month < MONTH_MIN || d.month > MONTH_MAX) {
        printInternalError("Invalid month!");
        revenue err = {-1};
        return err;
    }

    return revenueArr[d.year - 1970][d.month - 1];
}