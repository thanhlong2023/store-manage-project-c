#ifndef PRODUCT_H
#define PRODUCT_H

#define MAX_PRODUCTS 1000

typedef struct
{
    char categoryId[10];
    char productId[10];
    char productName[30];
    int quantity;
    int price;
} Product;

// Khai báo hàm xử lý Product
void printProduct(Product product);
void viewProducts();
void addProduct();
void updateProduct();
void deleteProduct();
void searchProduct();
void sortProduct();
void filterProduct();

#endif