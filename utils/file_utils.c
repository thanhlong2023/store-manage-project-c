#include "../include/file_utils.h"
#include "../include/category.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void saveToFile(const char *filename, void *array, int count, size_t elementSize)
{
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        printf("Cannot open file for writing!\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, file);    // Ghi số lượng phần tử
    fwrite(array, elementSize, count, file); // Ghi dữ liệu

    fclose(file);
}

int loadFromFile(const char *filename, void *array, int *count, size_t elementSize)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        printf("Cannot open file for reading!\n");
        return 0;
    }

    fread(count, sizeof(int), 1, file);      // Đọc số lượng phần tử
    fread(array, elementSize, *count, file); // Đọc dữ liệu và ghi dữ liệu vào mảng array

    fclose(file);
    return 1;
}

int cmpAscName(const void *a, const void *b)
{
    const Category *x = (Category *)a;
    const Category *y = (Category *)b;
    return strcmp(x->categoryName, y->categoryName);
}

int cmpDescName(const void *a, const void *b)
{
    const Category *x = (Category *)a;
    const Category *y = (Category *)b;
    return strcmp(y->categoryName, x->categoryName);
}

void printCentered(const char *text)
{
    int padding = (WIDTH - strlen(text)) / 2;
    printf("%*s%s\n", padding, "", text);
}

void pressEnterOrExit(int clearScreenAfter)
{
    char input;
    while (1)
    {
        printf("\nGo back (b) or Exit (0): ");
        input = getchar();
        while (getchar() != '\n')
            ; // xóa bộ đệm

        if (input == '0')
        {
            printf("Exiting the program...\n");
            exit(0);
        }
        else if (input == 'b')
        {
            if (clearScreenAfter)
            {
                // printf("\033[H\033[J"); // Clear screen command for Unix/Linux/macOS
                system("cls"); // Use this line for Windows
                // system("clear");
            }
            return;
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }
    }
}
