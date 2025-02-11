#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/product.h"
#include "../include/category.h"
#include "../include/file_utils.h"
#include "../include/validate.h"

Product products[MAX_PRODUCTS];
int productCount = 0;

Category categoriesCopy[MAX_CATEGORIES];
int categoryCountCopy = 0;

void viewProducts()
{
    if (productCount == 0)
    {
        printf("Sản phẩm trống.\n");
        return;
    }

    printf("\n***** PRODUCTS *****\n\n");
    printf("|============|======================|==========|=========|\n");
    printf("| ID         | Name                 | Quantity | Price   |\n");
    printf("|------------|----------------------|----------|---------|\n");
    for (int i = 0; i < productCount; i++)
    {
        printProduct(products[i]);
        if (i == productCount - 1)
            printf("|============|======================|==========|=========|\n");
        else
            printf("|------------|----------------------|----------|---------|\n");
    }
}

void printProduct(Product product)
{
    printf("| %-10s | %-20s | %8d | %7d |\n", product.productId, product.productName, product.quantity, product.price);
}

void addProduct()
{
    loadCategoriesFromFile("data/category.txt", categoriesCopy, &categoryCountCopy);
    if (productCount >= MAX_PRODUCTS)
    {
        printf("Danh sách sản phẩm đã đầy!\n");
        return;
    }

    Product newProduct;

    printf("Lựa chọn danh mục sản phẩm:\n");
    displayCategories();

    printf("Nhập Category ID: ");
    char categoryId[10];
    scanf("%s", categoryId);
    getchar();

    // kiểm tra categoryId co ton tai khong int found = 0;
    int found = 0;
    for (int i = 0; i < categoryCountCopy; i++)
    {
        if (strcmp(categoryId, categoriesCopy[i].categoryId) == 0)
        {
            found = 1;
            strcpy(newProduct.categoryId, categoryId);
            break;
        }
    }
    if (!found)
    {
        printf("Danh mục không tồn tại!\n");
        return;
    }

    printf("Nhập Product ID: ");
    char newProductId[10];
    scanf("%s", newProductId);
    getchar();
    // kiểm tra id sản phẩm có tồn tại không
    for (int i = 0; i < productCount; i++)
    {
        if (strcmp(newProductId, products[i].productId) == 0)
        {
            printf("ID sản phẩm đa da ton tai!\n");
            // trùng id thì chỉ thêm số lượng
            int addQuantity;
            printf("Nhập Quantity: ");
            scanf("%d", &addQuantity);
            checkNumber(&addQuantity);

            int totalQuantity = products[i].quantity + addQuantity;
            products[i].quantity = totalQuantity;
            printf("Them thanh cong!\n");
            getchar();
            return;
        }
    }
    strcpy(newProduct.productId, newProductId);

    printf("Nhập Product Name: ");
    fgets(newProduct.productName, sizeof(newProduct.productName), stdin);
    newProduct.productName[strlen(newProduct.productName) - 1] = '\0';

    int newQuantity;
    printf("Nhập Quantity: ");
    scanf("%d", &newQuantity);
    getchar();
    checkNumber(&newQuantity);
    newProduct.quantity = newQuantity;

    int newPrice;
    printf("Nhập Price: ");
    scanf("%d", &newPrice);
    getchar();
    checkNumber(&newPrice);
    newProduct.price = newPrice;

    products[productCount++] = newProduct;
    printf("Thêm sản phẩm thành công!\n");
}

void updateProduct()
{
    char updateProductId[10];
    printf("Nhập Product ID: ");
    scanf("%s", updateProductId);
    getchar();

    for (int i = 0; i < productCount; i++)
    {
        if (strcmp(updateProductId, products[i].productId) == 0)
        {
            char newProductName[30];
            int newQuantity, newPrice;

            printf("Nhập Product Name: ");
            fgets(newProductName, sizeof(newProductName), stdin);
            newProductName[strlen(newProductName) - 1] = '\0';

            printf("Nhập Quantity: ");
            scanf("%d", &newQuantity);
            getchar();
            checkNumber(&newQuantity);

            printf("Nhập Price: ");
            scanf("%d", &newPrice);
            getchar();
            checkNumber(&newPrice);

            strcpy(products[i].productName, newProductName);
            products[i].quantity = newQuantity;
            products[i].price = newPrice;
            printf("Cập nhật sản phẩm thành công!\n");
            return;
        }
        else
        {
            printf("Không tìm thấy sản phẩm!\n");
            return;
        }
    }
}

void deleteProduct()
{
    char deleteProductId[10];
    printf("Nhập Product ID: ");
    scanf("%s", deleteProductId);
    getchar();

    for (int i = 0; i < productCount; i++)
    {
        if (strcmp(deleteProductId, products[i].productId) == 0)
        {
            int choice;
            do
            {
                printf("Bạn có muốn xóa sản phẩm không.\n");
                printf("1. Yes\n");
                printf("2. No");
                switch (choice)
                {
                case 1:
                {
                    for (int j = i; j < productCount - 1; j++)
                    {
                        products[j] = products[j + 1];
                    }
                    productCount--;
                    printf("Xóa sản phẩm thành công!\n");
                    return;
                }
                case 2:
                    break;
                default:
                    printf("Lựa chọn không hợp lệ.");
                    break;
                }
            } while (choice != 2);
        }
        else
        {
            printf("Không tìm thấy sản phẩm!\n");
        }
    }
}
void searchProduct()
{
    char searchProductName[30];
    fgets(searchProductName, sizeof(searchProductName), stdin);
    searchProductName[strcspn(searchProductName, "\n")] = 0;

    toLowerCase(searchProductName);

    int found = 0;
    for (int i = 0; i < productCount; i++)
    {
        char tempProductName[30];
        strcpy(tempProductName, products[i].productName);
        toLowerCase(tempProductName);
        if (strstr(tempProductName, searchProductName))
        {
            printProduct(products[i]);
        }
    }
    if (!found)
        printf("Không tìm thấy sản phẩm nào\n");
}

void sortProduct()
{
    int choice;
    do
    {
        printf("1. Sắp xếp giá tăng dần.\n");
        printf("2. Sắp xếp giá dảm dần.\n");
        printf("0. Thoát.\n");
        printf("Lựa chọn: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
        {
            qsort(products, productCount, sizeof(Product), cmpAscPrice);
            viewProducts();
            return;
        }
        case 2:
        {
            qsort(products, productCount, sizeof(Product), cmpDescPrice);
            viewProducts();
            return;
        }
        case 0:
            break;
        default:
            printf("Lựa chọn không hợp lệ!\n");
            break;
        }
    } while (choice != 0);
}
void filterProduct()
{
    int choice;
    do
    {
        printf("1. Lọc sản phẩm theo Category.\n");
        printf("2. Lọc sản phẩm theo giá tiền.\n");
        printf("0. Thoát");
        printf("Lựa chọn: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            char filterID[10];
            printf("Nhập Category ID: ");
            scanf("%s", filterID);
            getchar();

            for (int i = 0; i < categoryCountCopy; i++)
            {
                if (strcmp(filterID, categoriesCopy[i].categoryId) == 0)
                {
                    int found = 0;
                    for (int i = 0; i < productCount; i++)
                    {
                        if (strcmp(filterID, products[i].categoryId) == 0)
                        {
                            printProduct(products[i]);
                            found = 1;
                            break;
                        }
                    }
                    if (!found)
                        printf("Không có sản phẩm.\n");
                }
                else
                {
                    printf("Danh mục không tồn tại.\n");
                    break;
                }
            }
        }
        case 2:
        {
            int startPrice, endPrice;
            printf("Nhập giá bắt đầu: ");
            scanf("%d", &startPrice);
            getchar();
            printf("Nhập giá kết thúc: ");
            scanf("%d", &endPrice);
            getchar();

            for (int i = 0; i < productCount; i++)
            {
                if (products[i].price < startPrice || products[i].price > endPrice)
                {
                    printf("Khoảng giá vô lý");
                }
                else
                {
                    printProduct(products[i]);
                }
            }
        }
        default:
            printf("Lựa chọn không hợp lệ.\n");
            break;
        }
    } while (choice != 0);
}