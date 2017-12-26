//
// Created by codgician on 12/22/2017.
//

#ifndef C_FINAL_EXAM_MACRO_H
#define C_FINAL_EXAM_MACRO_H

// Process bool type
#include <stdbool.h>
#define bool _Bool

// Input buffer
#define BUFFER_LENGTH 100
#define INT32_LENGTH 9
#define INT64_LENGTH 18

// Menu
#define EXIT_PROGRAM 0
#define MAIN_MENU 1
#define ROOM_MENU 2
#define CUSTOMER_MENU 3
#define REPORT_MENU 4


// Datetime
#define YEAR_MIN 1970
#define YEAR_MAX 9999
#define YEAR_COUNT 8030
#define MONTH_MIN 1
#define MONTH_MAX 12
#define MONTH_COUNT 12
#define HOUR_MIN 0
#define HOUR_MAX 23

// Define error status
#define SUCCESS 0x01

#define ERROR_INVALID_PRICE_TYPE 0x02
#define ERROR_INVALID_ROOM_TYPE 0x03

#define ERROR_INVALID_HOUR_PRICE 0x04
#define ERROR_INVALID_DAY_PRICE 0x05

#define ERROR_INVALID_DURATION 0x06

#define ERROR_INVALID_YEAR 0x07
#define ERROR_INVALID_MONTH 0x08
#define ERROR_INVALID_DAY 0x09
#define ERROR_INVALID_HOUR 0x10

#define ERROR_START_DATETIME_LARGER_THAN_END_DATETIME 0x11

#endif //C_FINAL_EXAM_MACRO_H
