//
// Created by codgician on 12/29/2017.
// This file contains a global variable "errorStatus",
// which indicates whether error occurs.
//

#include <stdio.h>
#include <stdlib.h>

#include "bool.h"
#include "error.h"

#define ERROR_MSG_LENGTH 100

bool errorStatus = false;

void createError(char *msg) {
    errorStatus = true;

    char *errorMsg = (char*)malloc(ERROR_MSG_LENGTH + 1);
    sprintf(errorMsg, "INTERNAL ERROR: %s\n", msg);
    fprintf(stderr, errorMsg);

    // Free pointer
    errorMsg = NULL;
    free(errorMsg);
}

void clearError() {
    errorStatus = false;
}
