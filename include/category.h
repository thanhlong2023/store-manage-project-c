#ifndef CATEGORY_H
#define CATEGORY_H

#include "product.h"

#define MAX_CATEGORIES 1000

typedef struct
{
    char categoryId[10];
    char categoryName[30];
} Category;

// Khai báo hàm xử lý Category
void displayCategories();
void displayCategoriesNotPress();
void addCategory();
void updateCategory();
void deleteCategory();
void searchCategory();
int cmpAsc(const void *a, const void *b);
int cmpDesc(const void *a, const void *b);
void sortCategory();
void sortCategory();

#endif
