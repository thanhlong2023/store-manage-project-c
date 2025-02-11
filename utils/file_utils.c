#include "../include/file_utils.h"
#include "../include/category.h"
#include <string.h>

void saveCategoriesToFile(const char *filename, Category *categories, int categoryCount)
{
    FILE *file = fopen(filename, "wb"); // Mở file ghi nhị phân
    if (!file)
    {
        printf("Khong the mo file de ghi!\n");
        return;
    }

    fwrite(&categoryCount, sizeof(int), 1, file);              // Ghi số lượng danh mục
    fwrite(categories, sizeof(Category), categoryCount, file); // Ghi danh mục

    fclose(file);
}

int loadCategoriesFromFile(const char *filename, Category *categories, int *categoryCount)
{
    FILE *file = fopen(filename, "rb"); // Mở file đọc nhị phân
    if (!file)
    {
        printf("Khong the mo file de doc!\n");
        return 0;
    }

    fread(categoryCount, sizeof(int), 1, file);                // Đọc số lượng danh mục
    fread(categories, sizeof(Category), *categoryCount, file); // Đọc danh mục

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

int cmpAscPrice(const void *a, const void *b)
{
    const Product *x = (Product *)a;
    const Product *y = (Product *)b;
    return x->price - y->price;
}
int cmpDescPrice(const void *a, const void *b)
{
    const Product *x = (Product *)a;
    const Product *y = (Product *)b;
    return y->price - x->price;
}