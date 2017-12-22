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

typedef struct _DatetimeReturn {
    int satus;
    int content;
} datetimeReturn;

int validateDatetime(datetime t);
int cmpDatetime(datetime a, datetime b);
datetimeReturn getIntervalDays(datetime startDatetime, datetime endDatetime);
datetimeReturn getIntervalHours(datetime startDatetime, datetime endDatetime);

#endif //C_FINAL_EXAM_DATETIME_H

