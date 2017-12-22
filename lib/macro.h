//
// Created by codgi on 12/22/2017.
//

#ifndef C_FINAL_EXAM_MACRO_H
#define C_FINAL_EXAM_MACRO_H

// Process bool type
#include <stdbool.h>
#define bool _Bool

// Datetime
#define YEAR_MIN 1970
#define YEAR_MAX 9999
#define YEAR_COUNT 8030
#define MONTH_MIN 1
#define MONTH_MAX 12
#define MONTH_COUNT 12

// Define error status
#define SUCCESS 0

#define ERROR_INVALID_PRICE_TYPE -1
#define ERROR_INVALID_ROOM_TYPE -2

#define ERROR_INVALID_HOUR_PRICE -3
#define ERROR_INVALID_DAY_PRICE -4

#define ERROR_INVALID_DURATION -5

#define ERROR_INVALID_YEAR -6
#define ERROR_INVALID_MONTH -7

#endif //C_FINAL_EXAM_MACRO_H
