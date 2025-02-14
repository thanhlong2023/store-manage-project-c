#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stddef.h>
#include "category.h"

// Hàm ghi mảng danh mục vào file nhị phân
void saveToFile(const char *filename, void *array, int cout, size_t elementSize);

// Hàm đọc mảng danh mục từ file nhị phân
int loadFromFile(const char *filename, void *array, int *count, size_t elementSize);

int cmpAscName(const void *a, const void *b);
int cmpDescName(const void *a, const void *b);

#define WIDTH 40 // Chiều rộng của dòng hiển thị

// Hàm in chuỗi căn giữa
void printCentered(const char *text);

void pressEnterOrExit(int clearScreenAfter);

#endif // FILE_UTILS_H
