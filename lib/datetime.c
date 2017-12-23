//
// Created by codgician on 12/22/2017.
//
// This file contains several functions
// that are related to datetime calculations.
//

#include "datetime.h"

int monthArr[MONTH_COUNT] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int getMonthDayCount(int month, int year) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    } else {
        return monthArr[month - 1];
    }
}

int getDayNumInYear(datetime t) {
    int result = 0;

    for (int i = 1; i < t.month; i++) {
        result += getMonthDayCount(i, t.year);
    }

    result += t.day;

    return result;
}

int validateDatetime(datetime t) {
    if (t.year < YEAR_MIN || t.year > YEAR_MAX) {
        return ERROR_INVALID_YEAR;
    }
    if (t.month < MONTH_MIN || t.month > MONTH_MAX) {
        return ERROR_INVALID_MONTH;
    }
    if (t.day > getMonthDayCount(t.month, t.year)) {
        return ERROR_INVALID_DAY;
    }
    if (t.hour < HOUR_MIN || t.hour > HOUR_MAX) {
        return ERROR_INVALID_HOUR;
    }
    return SUCCESS;
}

// 0: a < b, 1: a > b, 2: a == b
int cmpDatetime(datetime a, datetime b) {
    if (a.year == b.year) {
        if (a.month == b.month) {
            if (a.day == b.day) {
                if (a.hour == b.hour) {
                    return 2; // Identical
                }
            } else {
                return a.day > b.day;
            }
        } else {
            return a.month > b.month;
        }
    } else {
        return a.year > b.year;
    }
}

long long int getIntervalDays(datetime startDatetime, datetime endDatetime) {

    if (validateDatetime(startDatetime) != SUCCESS) {
        return validateDatetime(startDatetime);
    }

    if (validateDatetime(endDatetime) != SUCCESS) {
        return validateDatetime(endDatetime);
    }

    if (cmpDatetime(startDatetime, endDatetime) == 1) {
        return ERROR_START_DATETIME_LARGER_THAN_END_DATETIME;
    }

    long long int result = getDayNumInYear(endDatetime) - getDayNumInYear(startDatetime);

    for (int i = startDatetime.year + 1; i <= endDatetime.year - 1; i++) {
        result += (isLeapYear(i) ? 366 : 365);
    }

    return result;
}

long long int getIntervalHours(datetime startDatetime, datetime endDatetime) {

    if (validateDatetime(startDatetime) != SUCCESS) {
        return validateDatetime(startDatetime);
    }

    if (validateDatetime(endDatetime) != SUCCESS) {
        return validateDatetime(endDatetime);
    }

    if (cmpDatetime(startDatetime, endDatetime) == 1) {
        return ERROR_START_DATETIME_LARGER_THAN_END_DATETIME;
    }

    long long int result = endDatetime.hour - startDatetime.hour + getIntervalDays(startDatetime, endDatetime) * 24;

    return result;
}
