#include "include/menu.h"
#include "include/auth.h"
#include <stdio.h>

int main()
{
    if (loginAdmin("data/user.txt"))
    {
        printf("Login Successfully!\n");
        mainMenu(); // Gọi menu chính sau khi đăng nhập thành công
    }
    return 0;
}
// g++ -o store src/*.c main.cpp -Iinclude
// gcc -o exe src/*.c utils/*.c main.c -Iinclude