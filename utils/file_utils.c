#include "../include/file_utils.h"
#include "../include/category.h"
#include <string.h>

void saveToFile(const char *filename, void *array, int count, size_t elementSize)
{
    FILE *file = fopen(filename, "wb"); // Mở file ghi nhị phân
    if (!file)
    {
        printf("Khong the mo file de ghi!\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, file);    // Ghi số lượng phần tử
    fwrite(array, elementSize, count, file); // Ghi dữ liệu

    fclose(file);
}

int loadFromFile(const char *filename, void *array, int *count, size_t elementSize)
{
    FILE *file = fopen(filename, "rb"); // Mở file đọc nhị phân
    if (!file)
    {
        printf("Khong the mo file de doc!\n");
        return 0;
    }

    fread(count, sizeof(int), 1, file);      // Đọc số lượng phần tử
    fread(array, elementSize, *count, file); // Đọc dữ liệu vào mảng

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
