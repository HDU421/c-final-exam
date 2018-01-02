//
// Created by codgician on 12/22/2017.
//

#ifndef C_FINAL_EXAM_DATETIME_H
#define C_FINAL_EXAM_DATETIME_H

#define YEAR_MIN 1970
#define YEAR_MAX 9999
#define YEAR_COUNT 8030
#define MONTH_MIN 1
#define MONTH_MAX 12
#define MONTH_COUNT 12
#define HOUR_MIN 0
#define HOUR_MAX 23

#include "bool.h"
#include "error.h"

typedef struct _Datetime {
    int year;
    int month;
    int day;
    int hour;
} datetime;

int cmpDatetime(datetime a, datetime b);
int getMonthDayCount(int month, int year);
long long int getIntervalDays(datetime startDatetime, datetime endDatetime);
long long int getIntervalHours(datetime startDatetime, datetime endDatetime);

#endif //C_FINAL_EXAM_DATETIME_H

