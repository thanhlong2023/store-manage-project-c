
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../include/validate.h"

void checkNumber(int *number)
{
    // Nếu số nhập vào < 0, yêu cầu nhập lại
    while (*number < 0)
    {
        printf("Please enter a number greater than 0. Try again: ");
        scanf("%d", number);
        getchar();
    }
    return;
}
void toLowerCase(char *str)
{
    while (*str)
    {
        *str = tolower(*str);
        str++;
    }
}
