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
        printInternalError("Invalid price type", "getPrice");
        return -1;
    }

    if (duration < 0) {
        printInternalError("Invalid duration", "getPrice");
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
        printInternalError("Invalid price type", "checkIn");
        return false;
    }

    if (cmpDatetime(startDatetime, endDatetime, checkOption) == 1) {
        printInternalError("End datetime smaller than start datetime", "checkIn");
        return false;
    }

    long long int cntPrice = 0;
    if (priceType == HOUR_PRICE) {
        cntPrice = getPrice(roomInfo, priceType, (getMonthDayCount(startDatetime.month, startDatetime.year) - startDatetime.day) * HOUR_COUNT + (HOUR_MAX - startDatetime.hour + 1));
    } else {
        cntPrice = getPrice(roomInfo, priceType, getMonthDayCount(startDatetime.month, startDatetime.year) - startDatetime.day + 1);
    }
    revenueArr[startDatetime.year - YEAR_MIN][startDatetime.month - MONTH_MIN].expected += cntPrice;
    revenueArr[endDatetime.year - YEAR_MIN][endDatetime.month - MONTH_MIN].real += cntPrice;

    datetime cntDatetime = startDatetime;
    // cntDatetime++
    if (cntDatetime.month == 12) {
        cntDatetime.year++;
        cntDatetime.month = 1;
    } else {
        cntDatetime.month++;
    }
    while (cmpDatetime(cntDatetime, endDatetime, CHECK_YEAR + CHECK_MONTH) == 0) {
        if (priceType == HOUR_PRICE) {
            cntPrice = getPrice(roomInfo, priceType, getMonthDayCount(cntDatetime.month, cntDatetime.year) * HOUR_COUNT);
        } else {
            cntPrice = getPrice(roomInfo, priceType, getMonthDayCount(cntDatetime.month, cntDatetime.year));
        }
        revenueArr[cntDatetime.year - YEAR_MIN][cntDatetime.month - MONTH_MIN].expected += cntPrice;
        revenueArr[endDatetime.year - YEAR_MIN][endDatetime.month - MONTH_MIN].real += cntPrice;

        // cntDatetime++
        if (cntDatetime.month == 12) {
            cntDatetime.year++;
            cntDatetime.month = 1;
        } else {
            cntDatetime.month++;
        }
    }

    if (priceType == HOUR_PRICE) {
        cntPrice = getPrice(roomInfo, priceType, (endDatetime.day - 1) * HOUR_COUNT + endDatetime.hour);
    } else {
        cntPrice = getPrice(roomInfo, priceType, endDatetime.day - 1);
    }
    revenueArr[endDatetime.year - YEAR_MIN][endDatetime.month - MONTH_MIN].expected += cntPrice;
    revenueArr[endDatetime.year - YEAR_MIN][endDatetime.month - MONTH_MIN].real += cntPrice;

    return true;
}

/* Return financial report for a specific month */
revenue getReport(datetime d) {

    if (d.year < YEAR_MIN || d.year > YEAR_MAX) {
        printInternalError("Invalid year", "getReport");
        revenue err = {-1};
        return err;
    }

    if (d.month < MONTH_MIN || d.month > MONTH_MAX) {
        printInternalError("Invalid month", "getReport");
        revenue err = {-1};
        return err;
    }

    return revenueArr[d.year - 1970][d.month - 1];
}