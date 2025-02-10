#include <stdio.h>
#include "../include/date.h"

void printDate(Date date)
{
    printf("%02d/%02d/%04d", date.day, date.month, date.year);
}
