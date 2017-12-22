#include <stdio.h>

#include "misc.h"
#include "room.h"

int main(int argc, char *argv[])
{
    clearConsole();
    printf("Hello World!\n");
    int result = addNewRoom(1, 100, "FUCK");
    printf("result = %d\n", result);
    printf("roomPrice: hour = %d, day = %d\n", getRoomPrice(0, HOUR_PRICE), getRoomPrice(0, DAY_PRICE));
    return 0;
}