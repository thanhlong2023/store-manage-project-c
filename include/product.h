#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct
{
    char productId[10];
    char productName[30];
    int quantity;
    int price;
} Product;

// Khai báo hàm xử lý Product
void addProduct();
void viewProducts();
void printProduct(Product product);

#endif
