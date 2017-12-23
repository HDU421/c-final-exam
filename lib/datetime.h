//
// Created by codgician on 12/22/2017.
//

#ifndef C_FINAL_EXAM_MACRO_H
#include "macro.h"
#endif //C_FINAL_EXAM_MACRO_H

#ifndef C_FINAL_EXAM_DATETIME_H
#define C_FINAL_EXAM_DATETIME_H

typedef struct _Datetime {
    int year;
    int month;
    int day;
    int hour;
} datetime;

int validateDatetime(datetime t);
int cmpDatetime(datetime a, datetime b);
int getMonthDayCount(int month, int year);
long long int getIntervalDays(datetime startDatetime, datetime endDatetime);
long long int getIntervalHours(datetime startDatetime, datetime endDatetime);

#endif //C_FINAL_EXAM_DATETIME_H

