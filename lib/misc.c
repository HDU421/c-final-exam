//
// Created by codgician on 11/10/2017.
// This file contains several cross platform misc functions.
//

#include <stdlib.h>

void clearConsole()
{
    #if defined _WIN32 || defined _WIN64
        system("cls");
    #else
        system("clear");
    #endif
}
