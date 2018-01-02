//
// Created by codgician on 12/22/2017.
//

#ifndef C_FINAL_EXAM_ROOM_H
#include "room.h"
#endif //C_FINAL_EXAM_ROOM_H

#ifndef C_FINAL_EXAM_DATETIME_H
#include "datetime.h"
#endif //C_FINAL_EXAM_DATETIME_H

#ifndef C_FINAL_EXAM_CUSTOMER_H
#define C_FINAL_EXAM_CUSTOMER_H

#define ERR_CUSTOMER_DURATION_INVALID -1
#define ERR_

typedef struct _Revenue {
    long long int expected;
    long long int real;
} revenue;

void initRevenueArr();
long long int getPrice(room roomInfo, int priceType, long long int duration);
bool checkIn(room roomInfo, int priceType, datetime startDatetime, datetime endDatetime);
revenue getReport(int year, int month);

#endif //C_FINAL_EXAM_CUSTOMER_H
