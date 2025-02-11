#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include "category.h"

// Hàm ghi mảng danh mục vào file nhị phân
void saveCategoriesToFile(const char *filename, Category *categories, int categoryCount);

// Hàm đọc mảng danh mục từ file nhị phân
int loadCategoriesFromFile(const char *filename, Category *categories, int *categoryCount);

int cmpAscPrice(const void *a, const void *b);
int cmpDescPrice(const void *a, const void *b);

int cmpAscName(const void *a, const void *b);
int cmpDescName(const void *a, const void *b);

#endif // FILE_UTILS_H
