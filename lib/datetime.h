//
// Created by intochange on 12/22/2017.
//

#ifndef C_FINAL_EXAM_DATETIME_H
#define C_FINAL_EXAM_DATETIME_H

#include "bool.h"
#include "error.h"

#define YEAR_MIN 1970
#define YEAR_MAX 9999
#define YEAR_COUNT 8030
#define YEAR_DAY_LEAP 366
#define YEAR_DAY_COMMON 365
#define MONTH_MIN 1
#define MONTH_MAX 12
#define MONTH_COUNT 12
#define MONTH_DAY_FEB_COMMON 28
#define MONTH_DAY_FEB_LEAP 29
#define MONTH_DAT_LUNAR 30
#define MONTH_DAY_SOLAR 31
#define HOUR_MIN 0
#define HOUR_MAX 23
#define HOUR_COUNT 24

#define CHECK_YEAR 1
#define CHECK_MONTH 2
#define CHECK_DAY 4
#define CHECK_HOUR 8

typedef struct _Datetime {
    int year;
    int month;
    int day;
    int hour;
} datetime;

bool validateDatetime(datetime d, unsigned int option);
int cmpDatetime(datetime a, datetime b, unsigned int option);
int getMonthDayCount(int month, int year);
long long int getIntervalDays(datetime startDatetime, datetime endDatetime);
long long int getIntervalHours(datetime startDatetime, datetime endDatetime);

#endif //C_FINAL_EXAM_DATETIME_H

