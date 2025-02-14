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
        printf("List Products is empty!\n");
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
    pressEnterOrExit(1);
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
        printf("List Products is full!\n");
        return;
    }

    Product newProduct;

    printf("Choice Category:\n");
    // hiển thị category
    printf("\n***** CATEGORIES *****\n\n");
    printf("|=====|============|\n");
    printf("| %-3s | %-10s |\n", "ID", "Name");
    printf("|=====|============|\n");

    for (int i = 0; i < categoryCountCopy; i++)
    {
        printf("| %-3s | %-10s |\n", categoriesCopy[i].categoryId, categoriesCopy[i].categoryName);
        if (i == categoryCountCopy - 1)
            printf("|=====|============|\n");
        else
            printf("|-----|------------|\n");
    }

    printf("\nEnter Category ID: ");
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

            printf("Enter Product ID: ");
            char newProductId[10];
            fgets(newProductId, sizeof(newProductId), stdin);
            newProductId[strcspn(newProductId, "\n")] = '\0';

            // kiểm tra id sản phẩm có tồn tại không
            for (int i = 0; i < productCount; i++)
            {
                if (strcmp(newProductId, products[i].productId) == 0)
                {
                    // printf("ID sản phẩm đa da ton tai!\n");
                    printf("Product ID is exist!\n");
                    // trùng id thì chỉ thêm số lượng
                    int addQuantity;
                    // printf("Nhập Quantity: ");
                    printf("Enter Quantity: ");
                    scanf("%d", &addQuantity);
                    checkNumber(&addQuantity);
                    getchar();

                    int totalQuantity = products[i].quantity + addQuantity;
                    products[i].quantity = totalQuantity;
                    // printf("Them thanh cong!\n");
                    printf("\nAdd successfully!\n");
                    saveToFile("data/products.txt", products, productCount, sizeof(Product));

                    pressEnterOrExit(1);
                    return;
                }
            }
            strcpy(newProduct.productId, newProductId);

            // printf("Nhập Product Name: ");
            printf("Enter Product Name: ");
            fgets(newProduct.productName, sizeof(newProduct.productName), stdin);
            newProduct.productName[strlen(newProduct.productName) - 1] = '\0';

            int newQuantity;
            // printf("Nhập Quantity: ");
            printf("Enter Quantity: ");
            scanf("%d", &newQuantity);
            getchar();
            checkNumber(&newQuantity);
            newProduct.quantity = newQuantity;

            int newPrice;
            // printf("Nhập Price: ");
            printf("Enter Price: ");
            scanf("%d", &newPrice);
            getchar();
            checkNumber(&newPrice);
            newProduct.price = newPrice;

            products[productCount++] = newProduct;
            // printf("Thêm sản phẩm thành công!\n");
            printf("\nAdd product successfully!\n");

            saveToFile("data/products.txt", products, productCount, sizeof(Product));

            viewProducts();
            break;
        }
    }
    if (!found)
    {
        // printf("Danh mục không tồn tại!\n");
        printf("Category is not exist!\n");
        return;
    }
}

void updateProduct()
{
    loadFromFile("data/products.txt", products, &productCount, sizeof(Product));
    char updateProductId[10];
    // printf("Nhập Product ID: ");
    printf("Enter Product ID: ");
    fgets(updateProductId, sizeof(updateProductId), stdin);
    updateProductId[strcspn(updateProductId, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < productCount; i++)
    {
        if (strcmp(updateProductId, products[i].productId) == 0)
        {
            char newProductName[30];
            int newQuantity, newPrice;

            // printf("Nhập Product Name: ");
            printf("Enter Product Name: ");
            fgets(newProductName, sizeof(newProductName), stdin);
            newProductName[strlen(newProductName) - 1] = '\0';

            // printf("Nhập Quantity: ");
            printf("Enter Quantity: ");
            scanf("%d", &newQuantity);
            getchar();
            checkNumber(&newQuantity);

            // printf("Nhập Price: ");
            printf("Enter Price: ");
            scanf("%d", &newPrice);
            getchar();
            checkNumber(&newPrice);

            strcpy(products[i].productName, newProductName);
            products[i].quantity = newQuantity;
            products[i].price = newPrice;
            // printf("Cập nhật sản phẩm thành công!\n");
            printf("\nUpdate product successfully!\n");

            saveToFile("data/products.txt", products, productCount, sizeof(Product));

            viewProducts();
            return;
        }
    }
    if (!found)
        // printf("Không tìm thấy sản phẩm");
        printf("Product is not found!");
}

void deleteProduct()
{
    loadFromFile("data/products.txt", products, &productCount, sizeof(Product));
    char deleteProductId[10];
    // printf("Nhập Product ID: ");
    printf("Enter Product ID: ");
    fgets(deleteProductId, sizeof(deleteProductId), stdin);
    deleteProductId[strcspn(deleteProductId, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < productCount; i++)
    {
        int choice;
        if (strcmp(deleteProductId, products[i].productId) == 0)
        {
            found = 1;
            do
            {
                printf("\nProduct Information:\n");
                printf("ID: %s\n", products[i].productId);
                printf("Name: %s\n", products[i].productName);
                printf("Quantity: %d\n", products[i].quantity);
                printf("Price: %d\n", products[i].price);
                printf("\n");
                // printf("Bạn có muốn xóa sản phẩm không.\n");
                printf("Do you want to delete this product?\n");
                printf("1. Yes\n");
                printf("2. No\n");
                // printf("Nhập lựa chọn của bạn: ");
                printf("Enter your choice: ");

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
                    // printf("Xóa sản phẩm thành công!\n");
                    printf("Delete product successfully!\n");

                    saveToFile("data/products.txt", products, productCount, sizeof(Product));
                    choice = 2;
                    return;
                }
                case 2:
                    return;
                default:
                    // printf("Lựa chọn không hợp lệ.\n");
                    printf("Invalid choice!\n");
                    break;
                }
            } while (choice != 2);
        }
    }
    if (!found)
    {
        // printf("Không tìm thấy sản phẩm");
        printf("Product is not found!\n");
    }
}
void searchProduct()
{
    loadFromFile("data/products.txt", products, &productCount, sizeof(Product));
    // printf("Nhập tên sản phẩm cần tìm kiếm: ");
    printf("Enter product name to search: ");
    char searchProductName[30];
    fgets(searchProductName, sizeof(searchProductName), stdin);
    searchProductName[strcspn(searchProductName, "\n")] = 0;

    toLowerCase(searchProductName);

    int found = 0;
    printf("\n***** PRODUCTS *****\n\n");
    printf("|============|======================|==========|=========|\n");
    printf("| ID         | Name                 | Quantity | Price   |\n");
    printf("|------------|----------------------|----------|---------|\n");
    for (int i = 0; i < productCount; i++)
    {
        char tempProductName[30];
        strcpy(tempProductName, products[i].productName);
        toLowerCase(tempProductName);
        if (strstr(tempProductName, searchProductName))
        {
            printProduct(products[i]);
            found = 1;
            if (i == productCount - 1)
            {
                printf("|============|======================|==========|=========|\n");
            }
            else
            {
                printf("|------------|----------------------|----------|---------|\n");
            }
        }
    }
    if (!found)
    { // printf("Không tìm thấy sản phẩm nào\n");
        printf("No product found!\n");
    }
    pressEnterOrExit(1);
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
    // printf("Săp xếp thành công");
    printf("\nSorting successfully!\n");
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
    // printf("Săp xếp thành công");
    printf("\nSorting successfully!\n");
}
void sortProduct()
{
    loadFromFile("data/products.txt", products, &productCount, sizeof(Product));
    int choice;
    do
    {
        // printf("1. Sắp xếp giá tăng dần.\n");
        printf("[1]. Sort by price ascending.\n");
        // printf("2. Sắp xếp giá dảm dần.\n");
        printf("[2]. Sort by price descending.\n");
        // printf("0. Thoát.\n");
        printf("[0]. Exit.\n");
        // printf("Lựa chọn: ");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        printf("\033[H\033[J");
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
            // printf("Lựa chọn không hợp lệ!\n");
            printf("Invalid choice!\n");
            break;
        }
    } while (choice != 0);
}
void filterProduct()
{
    loadFromFile("data/category.txt", categoriesCopy, &categoryCountCopy, sizeof(Category));
    loadFromFile("data/products.txt", products, &productCount, sizeof(Product));
    int choice;
    do
    {
        printf("\n***** FILTER MENU *****\n\n");
        // printf("1. Lọc sản phẩm theo Category.\n");
        printf("[1]. Filter products by category.\n");
        // printf("2. Lọc sản phẩm theo giá tiền.\n");
        printf("[2]. Filter products by price.\n");
        // printf("0. Thoát\n");
        printf("[0]. Exit\n");
        // printf("Lựa chọn: ");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        printf("\033[H\033[J");
        switch (choice)
        {
        case 1:
        {
            displayCategoriesNotPress();
            char filterID[10];
            // printf("Nhập Category ID: ");
            printf("Enter Category ID: ");
            scanf("%s", filterID);
            getchar();
            printf("%s\n", filterID);

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
                        // printf("Không có sản phẩm.\n");
                        printf("No products found.\n");
                }
            }
            if (!foundCategory)
            {
                // printf("Danh mục không tồn tại.\n");
                printf("Category does not exist.\n");
            }
            break;
        }
        case 2:
        {
            double startPrice, endPrice;
            int found = 0;

            printf("\n***** FILTER MENU BY PRICE *****\n\n");
            // printf("Nhập giá bắt đầu: ");
            printf("Enter start price: ");
            scanf("%lf", &startPrice);
            // printf("Nhập giá kết thúc: ");
            printf("Enter end price: ");
            scanf("%lf", &endPrice);

            if (startPrice > endPrice)
            {
                printf("Khoảng giá vô lý!\n");
                break;
            }
            printf("\n***** PRODUCTS *****\n\n");
            printf("|============|======================|==========|=========|\n");
            printf("| ID         | Name                 | Quantity | Price   |\n");
            printf("|------------|----------------------|----------|---------|\n");
            for (int i = 0; i < productCount; i++)
            {
                if (products[i].price >= startPrice && products[i].price <= endPrice)
                {
                    printProduct(products[i]);
                    found = 1;
                    if (i == productCount - 1)
                        printf("|============|======================|==========|=========|\n");
                    else
                        printf("|------------|----------------------|----------|---------|\n");
                }
            }

            if (!found)
            {
                // printf("Không có sản phẩm nào trong khoảng giá này!\n");
                printf("No products within the specified price range!\n");
            }
            break;
        }

        default:
            // printf("Lựa chọn không hợp lệ.\n");
            printf("Invalid choice!\n");
            break;
        }
    } while (choice != 0);
}