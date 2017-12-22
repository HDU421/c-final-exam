//
// Created by codgi on 12/22/2017.
//

#include "macro.h"

int monthArr[MONTH_COUNT] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool validateYear(int year)
{
    return year < YEAR_MIN || year > YEAR_MAX;
}

bool validateMonth(int month)
{
    return month < MONTH_MIN || month > MONTH_MAX;
}

bool isLeapYear(int year)
{
    if (!validateYear(year))
        return ERROR_INVALID_YEAR;

    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int getMonthDayCount(int month, int year)
{
    if (!validateYear(year))
        return ERROR_INVALID_YEAR;
    if (!validateMonth(month))
        return ERROR_INVALID_MONTH;

    if (month == 2)
    {
        return isLeapYear(year) ? 29 : 28;
    }
    else
    {
        return monthArr[month - 1];
    }
}

