//
// Created by codgician on 12/22/2017.
//
// This file contains several functions
// that are related to datetime calculations.
//

#include "datetime.h"

// Days for each month
// Should not be used directly! Use getMonthDayCount(int month, int year) instead!
int monthArr[MONTH_COUNT] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/* Judge whether a given year is a leap year */
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/* Get day count of a certain month of a certain year */
int getMonthDayCount(int month, int year) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    } else {
        return monthArr[month - 1];
    }
}

/* Get the position of a specific date in its year */
int getDayNumInYear(datetime t) {
    int result = 0;

    // First count the days of full months
    for (int i = 1; i < t.month; i++) {
        result += getMonthDayCount(i, t.year);
    }

    // Add remaining days
    result += t.day;

    return result;
}

/* Validate given datetime */
bool validateDatetime(datetime t) {
    if (t.year < YEAR_MIN || t.year > YEAR_MAX) {
        return false;
    }
    if (t.month < MONTH_MIN || t.month > MONTH_MAX) {
        return false;
    }
    if (t.day > getMonthDayCount(t.month, t.year)) {
        return false;
    }
    if (t.hour < HOUR_MIN || t.hour > HOUR_MAX) {
        return false;
    }
    return true;
}

/* Compare two given datetime
 * a < b: return 0;
 * a > b: return 1;
 * a == b: return 2;
 */
int cmpDatetime(datetime a, datetime b) {
    if (a.year == b.year) {
        if (a.month == b.month) {
            if (a.day == b.day) {
                if (a.hour == b.hour) {
                    return 2; // Identical
                } else {
                    return a.hour > b.hour;
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

/* Get day count between two given datetimes */
long long int getIntervalDays(datetime startDatetime, datetime endDatetime) {

    if (!validateDatetime(startDatetime) || !validateDatetime(endDatetime)) {
        printInternalError("Invalid start datetime or end datetime");
        return -1;
    }

    if (cmpDatetime(startDatetime, endDatetime) == 1) {
        printInternalError("End datetime smaller than start datetime.");
        return -1;
    }

    long long int result = getDayNumInYear(endDatetime) - getDayNumInYear(startDatetime);
    for (int i = startDatetime.year + 1; i <= endDatetime.year - 1; i++) {
        result += (isLeapYear(i) ? 366 : 365);
    }

    return result;
}

/* Get hour count between two given datetime */
long long int getIntervalHours(datetime startDatetime, datetime endDatetime) {

    if (!validateDatetime(startDatetime) || !validateDatetime(endDatetime)) {
        printInternalError("Invalid start datetime or end datetime");
        return -1;
    }

    if (cmpDatetime(startDatetime, endDatetime) == 1) {
        printInternalError("End datetime smaller than start datetime.");
        return -1;
    }

    long long int result = endDatetime.hour - startDatetime.hour + getIntervalDays(startDatetime, endDatetime) * 24;

    return result;
}
