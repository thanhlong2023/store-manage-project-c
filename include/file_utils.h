#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include "category.h"

// Hàm ghi mảng danh mục vào file nhị phân
void saveToFile(const char *filename, void *array, int cout, size_t elementSize);

// Hàm đọc mảng danh mục từ file nhị phân
int loadFromFile(const char *filename, void *array, int *count, size_t elementSize);

int cmpAscName(const void *a, const void *b);
int cmpDescName(const void *a, const void *b);

#endif // FILE_UTILS_H
