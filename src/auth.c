#include <stdio.h>
#include <string.h>
#include "../include/auth.h"

int loginAdmin(const char *filename)
{
    char username[50], password[50];

    while (1)
    {
        printf("Nhap username: ");
        scanf("%s", username);
        getchar();
        printf("Nhap password: ");
        scanf("%s", password);
        getchar();

        FILE *file = fopen(filename, "r");
        if (!file)
        {
            printf("Khong the mo file!\n");
            return 0;
        }

        char fileUser[50], filePass[50];
        while (fscanf(file, "%s %s", fileUser, filePass) != EOF)
        {
            if (strcmp(fileUser, username) == 0 && strcmp(filePass, password) == 0)
            {
                fclose(file);
                return 1; // Đăng nhập thành công
            }
        }

        fclose(file);
        printf("Sai tai khoan hoac mat khau.\n");
    }
}
