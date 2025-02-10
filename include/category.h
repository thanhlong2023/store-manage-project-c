#ifndef CATEGORY_H
#define CATEGORY_H

#include "product.h"

#define MAX_PRODUCTS 100
#define MAX_CATEGORIES 100

typedef struct
{
    char categoryId[10];
    char categoryName[30];
    Product products[MAX_PRODUCTS]; // (Có thể sử dụng để lưu sản phẩm thuộc danh mục)
    int productCount;               // vì dùng mảng tĩnh, để xác định số lượng thực tế
} Category;

// Khai báo hàm xử lý Category
void displayCategories();
void addCategory();
void updateCategory();
void deleteCategory();
void searchCategory();
int cmpAsc(const void *a, const void *b);
int cmpDesc(const void *a, const void *b);
void sortCategory();
void sortCategory();

#endif
