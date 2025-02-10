#include <stdio.h>
#include "../include/product.h"

#define MAX_PRODUCTS 100

Product products[MAX_PRODUCTS];
int productCount = 0;

void addProduct()
{
    if (productCount >= MAX_PRODUCTS)
    {
        printf("Product list is full!\n");
        return;
    }

    Product newProduct;
    printf("Enter Product ID: ");
    scanf("%s", newProduct.productId);
    printf("Enter Product Name: ");
    scanf("%s", newProduct.productName);
    printf("Enter Quantity: ");
    scanf("%d", &newProduct.quantity);
    printf("Enter Price: ");
    scanf("%d", &newProduct.price);

    products[productCount++] = newProduct;
    printf("Product added successfully!\n");
}

void viewProducts()
{
    if (productCount == 0)
    {
        printf("No products available.\n");
        return;
    }

    printf("\n===== PRODUCTS =====\n");
    for (int i = 0; i < productCount; i++)
    {
        printf("Product %d:\n", i + 1);
        printProduct(products[i]);
    }
    printf("====================\n");
}

void printProduct(Product product)
{
    printf("ID: %s, Name: %s, Quantity: %d, Price: %d\n",
           product.productId, product.productName, product.quantity, product.price);
}
