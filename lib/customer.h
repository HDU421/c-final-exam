//
// Created by codgician on 12/22/2017.
//

#ifndef C_FINAL_EXAM_CUSTOMER_H
#define C_FINAL_EXAM_CUSTOMER_H

#include "bool.h"
#include "error.h"
#include "room.h"
#include "datetime.h"

typedef struct _Revenue {
    long long int expected;
    long long int real;
} revenue;

void initRevenueArr();
long long int getPrice(room roomInfo, int priceType, long long int duration);
bool checkIn(room roomInfo, int priceType, datetime startDatetime, datetime endDatetime);
revenue getReport(datetime d);

#endif //C_FINAL_EXAM_CUSTOMER_H
