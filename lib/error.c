//
// Created by codgician on 12/29/2017.
// This file contains a global variable "errorStatus",
// which indicates whether error occurs.
//

#include <stdio.h>

void printInternalError(char *msg, char *at) {
    fprintf(stderr, "INTERNAL ERROR: %s at %s\n", msg, at);
}
