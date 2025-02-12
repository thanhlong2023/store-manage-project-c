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
    loadFromFile("data/products.txt", products, &productCount, sizeof(Product));
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
    loadFromFile("data/products.txt", products, &productCount, sizeof(Product));
    loadFromFile("data/category.txt", categoriesCopy, &categoryCountCopy, sizeof(Category));
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
    fgets(categoryId, sizeof(categoryId), stdin);
    categoryId[strcspn(categoryId, "\n")] = '\0';

    // kiểm tra categoryId co ton tai khong int found = 0;
    int found = 0;
    for (int i = 0; i < categoryCountCopy; i++)
    {
        if (strcmp(categoryId, categoriesCopy[i].categoryId) == 0)
        {
            found = 1;
            strcpy(newProduct.categoryId, categoryId);

            printf("Nhập Product ID: ");
            char newProductId[10];
            fgets(newProductId, sizeof(newProductId), stdin);
            newProductId[strcspn(newProductId, "\n")] = '\0';

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
                    getchar();

                    int totalQuantity = products[i].quantity + addQuantity;
                    products[i].quantity = totalQuantity;
                    printf("Them thanh cong!\n");
                    saveToFile("data/products.txt", products, productCount, sizeof(Product));
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

            saveToFile("data/products.txt", products, productCount, sizeof(Product));
            break;
        }
    }
    if (!found)
    {
        printf("Danh mục không tồn tại!\n");
        return;
    }
}

void updateProduct()
{
    loadFromFile("data/products.txt", products, &productCount, sizeof(Product));
    char updateProductId[10];
    printf("Nhập Product ID: ");
    fgets(updateProductId, sizeof(updateProductId), stdin);
    updateProductId[strcspn(updateProductId, "\n")] = '\0';

    int found = 0;
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

            saveToFile("data/products.txt", products, productCount, sizeof(Product));
            return;
        }
    }
    if (!found)
        printf("Không tìm thấy sản phẩm");
}

void deleteProduct()
{
    loadFromFile("data/products.txt", products, &productCount, sizeof(Product));
    char deleteProductId[10];
    printf("Nhập Product ID: ");
    fgets(deleteProductId, sizeof(deleteProductId), stdin);
    deleteProductId[strcspn(deleteProductId, "\n")] = '\0';

    for (int i = 0; i < productCount; i++)
    {
        int choice;
        if (strcmp(deleteProductId, products[i].productId) == 0)
        {
            do
            {
                printf("Bạn có muốn xóa sản phẩm không.\n");
                printf("1. Yes\n");
                printf("2. No\n");
                printf("Nhập lựa chọn của bạn: ");

                scanf("%d", &choice);
                getchar();

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

                    saveToFile("data/products.txt", products, productCount, sizeof(Product));
                    choice = 2;
                    return;
                }
                case 2:
                    return;
                default:
                    printf("Lựa chọn không hợp lệ.\n");
                    break;
                }
            } while (choice != 2);
        }
    }
}
void searchProduct()
{
    loadFromFile("data/products.txt", products, &productCount, sizeof(Product));
    printf("Nhập tên sản phẩm cần tìm kiếm: ");
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
            found = 1;
        }
    }
    if (!found)
        printf("Không tìm thấy sản phẩm nào\n");
}
void bubbleSortAsc(Product arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].price > arr[j + 1].price)
            {
                Product temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("Săp xếp thành công");
}
void bubbleSortDesc(Product arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].price < arr[j + 1].price)
            {
                Product temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("Săp xếp thành công");
}
void sortProduct()
{
    loadFromFile("data/products.txt", products, &productCount, sizeof(Product));
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
            bubbleSortAsc(products, productCount);

            saveToFile("data/products.txt", products, productCount, sizeof(Product));
            viewProducts();
            break;
        }
        case 2:
        {
            bubbleSortDesc(products, productCount);

            saveToFile("data/products.txt", products, productCount, sizeof(Product));
            viewProducts();
            break;
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
    loadFromFile("data/category.txt", categoriesCopy, &categoryCountCopy, sizeof(Category));
    int choice;
    do
    {
        printf("1. Lọc sản phẩm theo Category.\n");
        printf("2. Lọc sản phẩm theo giá tiền.\n");
        printf("0. Thoát\n");
        printf("Lựa chọn: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            displayCategories();
            char filterID[10];
            printf("Nhập Category ID: ");
            scanf("%s", filterID);
            getchar();

            int foundCategory = 0;
            for (int i = 0; i < categoryCountCopy; i++)
            {
                if (strcmp(filterID, categoriesCopy[i].categoryId) == 0)
                {
                    foundCategory = 1;
                    int found = 0;
                    for (int i = 0; i < productCount; i++)
                    {
                        if (strcmp(filterID, products[i].categoryId) == 0)
                        {
                            printProduct(products[i]);
                            found = 1;
                        }
                    }
                    if (!found)
                        printf("Không có sản phẩm.\n");
                }
            }
            if (!foundCategory)
            {
                printf("Danh mục không tồn tại.\n");
            }
            break;
        }
        case 2:
        {
            double startPrice, endPrice;
            int found = 0; // Cờ kiểm tra có sản phẩm nào hợp lệ không

            printf("Nhập giá bắt đầu: ");
            scanf("%lf", &startPrice);
            printf("Nhập giá kết thúc: ");
            scanf("%lf", &endPrice);

            if (startPrice > endPrice) // Kiểm tra nhập sai
            {
                printf("Khoảng giá vô lý!\n");
                break;
            }

            for (int i = 0; i < productCount; i++)
            {
                if (products[i].price >= startPrice && products[i].price <= endPrice)
                {
                    printProduct(products[i]);
                    found = 1; // Đánh dấu tìm thấy ít nhất một sản phẩm
                }
            }

            if (!found)
            {
                printf("Không có sản phẩm nào trong khoảng giá này!\n");
            }
            break;
        }

        default:
            printf("Lựa chọn không hợp lệ.\n");
            break;
        }
    } while (choice != 0);
}