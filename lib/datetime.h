//
// Created by intochange on 12/22/2017.
//

#ifndef C_FINAL_EXAM_DATETIME_H
#define C_FINAL_EXAM_DATETIME_H

#include "bool.h"
#include "error.h"

#define YEAR_MIN 1970               // Minimum support year
#define YEAR_MAX 9999               // Maximum support year
#define YEAR_COUNT 8030             // Total support year count
#define YEAR_DAY_COMMON 365         // Common year day count
#define YEAR_DAY_LEAP 366           // Leap year day count
#define MONTH_MIN 1                 // Minimum support month
#define MONTH_MAX 12                // Maximum support month
#define MONTH_COUNT 12              // Total support month count
#define MONTH_DAY_FEB_COMMON 28     // Days of February in common years
#define MONTH_DAY_FEB_LEAP 29       // Days of February in leap years
#define MONTH_DAT_LUNAR 30          // Days of lunar months
#define MONTH_DAY_SOLAR 31          // Days of solar months
#define HOUR_MIN 0                  // Minimum support hour
#define HOUR_MAX 23                 // Maximum support hour
#define HOUR_COUNT 24               // Total support hour count

#define CHECK_YEAR 1                // 0001
#define CHECK_MONTH 2               // 0010
#define CHECK_DAY 4                 // 0100
#define CHECK_HOUR 8                // 1000

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

