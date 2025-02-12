// #include <stdio.h>
// #include <string.h>
// #include "../include/auth.h"

// int loginAdmin(const char *filename)
// {
//     char username[50], password[50];

//     while (1)
//     {
//         printf("Nhap username: ");
//         scanf("%s", username);
//         getchar();
//         printf("Nhap password: ");
//         scanf("%s", password);
//         getchar();

//         FILE *file = fopen(filename, "r");
//         if (!file)
//         {
//             printf("Khong the mo file!\n");
//             return 0;
//         }

//         char fileUser[50], filePass[50];
//         while (fscanf(file, "%s %s", fileUser, filePass) != EOF)
//         {
//             if (strcmp(fileUser, username) == 0 && strcmp(filePass, password) == 0)
//             {
//                 fclose(file);
//                 return 1; // Đăng nhập thành công
//             }
//         }

//         fclose(file);
//         printf("Sai tai khoan hoac mat khau.\n");
//     }
// }

#include <stdio.h>
#include <string.h>
#include <conio.h> // Thư viện cho _getch() trên Windows
#include "../include/auth.h"

// Hàm đọc mật khẩu và hiển thị *
void getPassword(char *password, int max_length)
{
    int i = 0;
    char ch;

    while (1)
    {
        ch = _getch(); // Đọc ký tự mà không hiển thị trên màn hình

        if (ch == 13)
        {                       // Enter (ASCII 13)
            password[i] = '\0'; // Kết thúc chuỗi
            break;
        }
        else if (ch == 8)
        { // Backspace (ASCII 8)
            if (i > 0)
            {
                i--;
                printf("\b \b"); // Xóa ký tự trên màn hình
            }
        }
        else if (i < max_length - 1)
        {
            password[i++] = ch;
            printf("*"); // Hiển thị dấu *
        }
    }
    printf("\n"); // Xuống dòng sau khi nhập xong
}

int loginAdmin(const char *filename)
{
    char username[50], password[50];

    while (1)
    {
        printf("Nhap username: ");
        scanf("%49s", username);
        // Xóa bộ đệm đầu vào
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        printf("Nhap password: ");
        getPassword(password, sizeof(password));

        FILE *file = fopen(filename, "r");
        if (!file)
        {
            printf("Khong the mo file!\n");
            return 0;
        }

        char fileUser[50], filePass[50];
        int found = 0;
        while (fscanf(file, "%49s %49s", fileUser, filePass) != EOF)
        {
            if (strcmp(fileUser, username) == 0 && strcmp(filePass, password) == 0)
            {
                found = 1;
                break;
            }
        }
        fclose(file);

        if (found)
        {
            return 1; // Đăng nhập thành công
        }
        else
        {
            printf("Sai tai khoan hoac mat khau.\n");
        }
    }
}