
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../include/validate.h"

void toLowerCase(char *str)
{
    while (*str)
    {
        *str = tolower(*str);
        str++;
    }
}
