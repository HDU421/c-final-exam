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

/* Validate given datetime
 * As for options, we've used bitwise to store it
 * CHECK_YEAR   0001 (1): Validate year
 * CHECK_MONTH  0010 (2): Validate month
 * CHECK_DAY    0100 (4): Validate day
 * CHECK_HOUR   1000 (8): Validate hour
 */
bool validateDatetime(datetime d, unsigned int option) {

    if ((option & CHECK_YEAR) && (d.year < YEAR_MIN || d.year > YEAR_MAX)) {
        return false;
    }
    if ((option & CHECK_MONTH) && (d.month < MONTH_MIN || d.month > MONTH_MAX)) {
        return false;
    }
    if ((option & CHECK_DAY) && (d.day > getMonthDayCount(d.month, d.year))) {
        return false;
    }
    if ((option & CHECK_HOUR) && (d.hour < HOUR_MIN || d.hour > HOUR_MAX)) {
        return false;
    }
    return true;
}

/* Compare two given datetime
 * a < b: return 0;
 * a > b: return 1;
 * a == b: return 2;
 * The usage of "option" is the same as "option" in validateDatetime().
 */
int cmpDatetime(datetime a, datetime b, unsigned int option) {
    if ((option & CHECK_YEAR) && a.year != b.year) {
        return a.year > b.year;
    }
    if ((option & CHECK_MONTH) && a.month != b.month) {
        return a.month > b.month;
    }
    if ((option & CHECK_DAY) && a.day != b.day) {
        return a.day > b.day;
    }
    if ((option & CHECK_HOUR) && a.hour != b.hour) {
        return a.hour > b.hour;
    }

    // Otherwise they they must be identical!
    return 2;
}

/* Get day count between two given datetimes */
long long int getIntervalDays(datetime startDatetime, datetime endDatetime) {

    unsigned int checkOption = CHECK_YEAR + CHECK_MONTH + CHECK_DAY;
    if (!validateDatetime(startDatetime, checkOption) || !validateDatetime(endDatetime, checkOption)) {
        printInternalError("Invalid start datetime or end datetime");
        return -1;
    }

    if (cmpDatetime(startDatetime, endDatetime, checkOption) == 1) {
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

    unsigned int checkOption = CHECK_YEAR + CHECK_MONTH + CHECK_DAY + CHECK_HOUR;
    if (!validateDatetime(startDatetime, checkOption) || !validateDatetime(endDatetime, checkOption)) {
        printInternalError("Invalid start datetime or end datetime");
        return -1;
    }

    if (cmpDatetime(startDatetime, endDatetime, checkOption) == 1) {
        printInternalError("End datetime smaller than start datetime.");
        return -1;
    }

    long long int result = endDatetime.hour - startDatetime.hour + getIntervalDays(startDatetime, endDatetime) * 24;

    return result;
}
