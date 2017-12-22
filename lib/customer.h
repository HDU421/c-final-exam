//
// Created by codgician on 12/22/2017.
//

#ifndef C_FINAL_EXAM_MACRO_H
#include "macro.h"
#endif //C_FINAL_EXAM_MACRO_H

#ifndef C_FINAL_EXAM_ROOM_H
#include "room.h"
#endif //C_FINAL_EXAM_ROOM_H

#ifndef C_FINAL_EXAM_DATETIME_H
#include "datetime.h"
#endif //C_FINAL_EXAM_DATETIME_H

#ifndef C_FINAL_EXAM_CUSTOMER_H
#define C_FINAL_EXAM_CUSTOMER_H

typedef struct _CustomerReturn {
    int status;
    int content;
} customerReturn;

typedef struct _Revenue {
    int expected;
    int real;
} revenue;

void initRevenueArr();
customerReturn getPrice(room roomInfo, int priceType, int duration);
int checkIn(room roomInfo, datetime startDatetime, datetime endDatetime);

#endif //C_FINAL_EXAM_CUSTOMER_H
