
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../include/validate.h"

void checkNumber(int *number)
{
    // Nếu số nhập vào < 0, yêu cầu nhập lại
    while (*number < 0)
    {
        printf("Phải nhập số lớn hơn 0. Nhập lại: ");
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
