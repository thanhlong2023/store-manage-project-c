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
    printf("|============|================================|==========|==========|\n");
    printf("| %-10s | %-30s | %8s | %8s |\n", "ID", "Product Name", "Quantity", "Price");
    printf("|============|================================|==========|==========|\n");
    for (int i = 0; i < productCount; i++)
    {
        printProduct(products[i]);
        if (i == productCount - 1)
            printf("|============|================================|==========|==========|\n");
        else
            printf("|------------|--------------------------------|----------|----------|\n");
    }
    pressEnterOrExit(1);
}

void printProduct(Product product)
{
    printf("| %-10s | %-30s | %8d | %8d |\n", product.productId, product.productName, product.quantity, product.price);
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

    printf("Choice Category:\n");
    // hiển thị category
    printf("\n***** CATEGORIES *****\n\n");
    printf("==================================================\n");
    printf("| %-10s | %-30s |\n", "ID", "Name");
    printf("==================================================\n");

    for (int i = 0; i < categoryCountCopy; i++)
    {
        printf("| %-3s | %-30s |\n", categoriesCopy[i].categoryId, categoriesCopy[i].categoryName);
        if (i == categoryCountCopy - 1)
            printf("==================================================\n");
        else
            printf("--------------------------------------------------\n");
    }

    int flag;
    char categoryId[110];
    do
    {
        flag = 0;
        printf("\nEnter Category ID (Enter 0 to cancel): ");
        fgets(categoryId, sizeof(categoryId), stdin);
        categoryId[strcspn(categoryId, "\n")] = '\0';

        if (strcmp(categoryId, "0") == 0)
        {
            system("cls");
            printf("Operation cancelled.\n");
            return;
        }
        // kiểm tra độ dài
        if (strlen(categoryId) > 10)
        {
            printf("Category ID must be less than 10 characters!\n");
            flag = 1;
            continue;
        }
        // kiểm tra rỗng
        if (categoryId[0] == '\0')
        {
            printf("Category ID must not be empty!\n");
            flag = 1;
            continue;
        }
        // kiểm tra id chưa tồn tại không được thêm sản phẩm

        for (int i = 0; i < categoryCountCopy; i++)
        {
            if (strcmp(categoryId, categoriesCopy[i].categoryId) == 0)
            {

                break;
            }
            else
            {
                printf("Category ID does not exist!\n");
                flag = 1;
                break;
            }
        }

    } while (flag);

    char newProductId[110];
    char newProductName[130];
    int newQuantity, newPrice;
    do
    {
        flag = 0;
        printf("\nEnter Product ID (Enter 0 to cancel): ");
        fgets(newProductId, sizeof(newProductId), stdin);
        newProductId[strcspn(newProductId, "\n")] = '\0';

        if (strcmp(newProductId, "0") == 0)
        {
            system("cls");
            printf("Operation cancelled.\n");
            return;
        }
        // kiểm tra độ dài
        if (strlen(newProductId) > 10)
        {
            printf("Product ID must be less than 10 characters!\n");
            flag = 1;
            continue;
        }
        // kiểm tra rỗng
        if (newProductId[0] == '\0')
        {
            printf("Product ID must not be empty!\n");
            flag = 1;
            continue;
        }
        // kiểm tra trùng id
        int isExist = 0;
        for (int i = 0; i < productCount; i++)
        {
            if (strcmp(newProductId, products[i].productId) == 0)
            {
                isExist = 1;
                break;
            }
        }
        if (isExist == 1)
        {
            printf("Product ID already exist! Please choose another ID\n");
            flag = 1;
            continue;
        }
    } while (flag);

    do
    {
        flag = 0;
        printf("\nEnter Product Name (Enter 0 to cancel): ");
        fgets(newProductName, sizeof(newProductName), stdin);
        newProductName[strcspn(newProductName, "\n")] = '\0';

        if (strcmp(newProductName, "0") == 0)
        {
            system("cls");
            printf("Operation cancelled.\n");
            return;
        }
        // kiểm tra độ dài
        if (strlen(newProductName) > 30)
        {
            printf("Product Name must be less than 30 characters!\n");
            flag = 1;
            continue;
        }
        // kiểm tra rỗng
        if (newProductName[0] == '\0')
        {
            printf("Product Name must not be empty!\n");
            flag = 1;
            continue;
        }
        // kiểm tra trùng name
        int isExist = 0;
        for (int i = 0; i < productCount; i++)
        {
            if (strcmp(newProductName, products[i].productName) == 0)
            {
                isExist = 1;
                break;
            }
        }
        if (isExist == 1)
        {
            printf("Product Name already exist! Please choose another Name\n");
            flag = 1;
            continue;
        }
    } while (flag);

    do
    {
        flag = 0;
        printf("\nEnter Quantity (Enter 0 to cancel): ");
        scanf("%d", &newQuantity);
        getchar();

        if (strcmp(newProductId, "0") == 0)
        {
            system("cls");
            printf("Operation cancelled.\n");
            return;
        }

        // kiểm tra số nguyên
        if (newQuantity < 0)
        {
            printf("Quantity must be a positive number!\n");
            flag = 1;
            continue;
        }

    } while (flag);

    do
    {
        flag = 0;
        printf("\nEnter Price (Enter 0 to cancel): ");
        scanf("%d", &newPrice);
        getchar();

        if (strcmp(newProductId, "0") == 0)
        {
            system("cls");
            printf("Operation cancelled.\n");
            return;
        }

        // kiểm tra số nguyên
        if (newPrice < 0)
        {
            printf("Price must be a positive number!\n");
            flag = 1;
            continue;
        }

    } while (flag);

    strcpy(products[productCount].categoryId, categoryId);
    strcpy(products[productCount].productId, newProductId);
    strcpy(products[productCount].productName, newProductName);
    products[productCount].quantity = newQuantity;
    products[productCount].price = newPrice;
    productCount++;

    saveToFile("data/products.txt", products, productCount, sizeof(Product));
    printf("Product added successfully!\n");

    viewProducts();
}

void updateProduct()
{
    loadFromFile("data/products.txt", products, &productCount, sizeof(Product));

    char updateProductId[100];
    int flag;
    do
    {
        flag = 0;

        printf("\nEnter Product ID (Enter 0 to cancel): ");
        fgets(updateProductId, sizeof(updateProductId), stdin);
        updateProductId[strcspn(updateProductId, "\n")] = '\0';

        if (strcmp(updateProductId, "0") == 0)
        {
            system("cls");
            printf("Operation cancelled.\n");
            return;
        }

        // kiểm tra độ dài
        if (strlen(updateProductId) > 10)
        {
            printf("Product ID must be less than 10 characters!\n");
            continue;
        }
        // kiểm tra rỗng
        if (updateProductId[0] == '\0')
        {
            printf("Product ID must not be empty!\n");
            continue;
        }

        int isExist = 0;
        for (int i = 0; i < productCount; i++)
        {
            if (strcmp(updateProductId, products[i].productId) == 0)
            {
                isExist = 1;
                break;
            }
        }
        if (isExist == 0)
        {
            printf("Can't find Product!\n");
            flag = 1;
            continue;
        }
    } while (flag);

    char updateProductName[100];
    do
    {
        flag = 0;
        printf("\nEnter Product Name (Enter 0 to cancel): ");
        fgets(updateProductName, sizeof(updateProductName), stdin);
        updateProductName[strcspn(updateProductName, "\n")] = '\0';

        if (strcmp(updateProductName, "0") == 0)
        {
            system("cls");
            printf("Operation cancelled.\n");
            return;
        }

        // kiểm tra độ dài
        if (strlen(updateProductName) > 30)
        {
            printf("Product Name must be less than 30 characters!\n");
            flag = 1;
            continue;
        }
        // kiểm tra rỗng
        if (updateProductName[0] == '\0')
        {
            printf("Product Name must not be empty!\n");
            flag = 1;
            continue;
        }

        int isExist = 0;
        for (int i = 0; i < productCount; i++)
        {
            if (strcmp(updateProductName, products[i].productName) == 0)
            {
                isExist = 1;
                break;
            }
        }
        if (isExist)
        {
            printf("Product Name is exist!\n");
            flag = 1;
            continue;
        }
    } while (flag);

    int newQuantity;
    do
    {
        flag = 0;
        printf("\nEnter Quantity (Enter 0 to cancel): ");
        scanf("%d", &newQuantity);
        getchar();

        if (strcmp(updateProductId, "0") == 0)
        {
            system("cls");
            printf("Operation cancelled.\n");
            return;
        }

        if (newQuantity < 0)
        {
            printf("Quantity must be a positive number!\n");
            flag = 1;
            continue;
        }

    } while (flag);

    int newPrice;
    do
    {
        flag = 0;
        printf("\nEnter Price (Enter 0 to cancel): ");
        scanf("%d", &newPrice);
        getchar();

        if (strcmp(updateProductId, "0") == 0)
        {
            system("cls");
            printf("Operation cancelled.\n");
            return;
        }

        if (newPrice < 0)
        {
            printf("Price must be a positive number!\n");
            flag = 1;
            continue;
        }

    } while (flag);

    for (int i = 0; i < productCount; i++)
    {
        if (strcmp(updateProductId, products[i].productId) == 0)
        {
            strcpy(products[i].productName, updateProductName);
            products[i].quantity = newQuantity;
            products[i].price = newPrice;

            break;
        }
    }

    printf("Product updated successfully!\n");
    saveToFile("data/products.txt", products, productCount, sizeof(Product));

    viewProducts();
}

void deleteProduct()
{
    loadFromFile("data/products.txt", products, &productCount, sizeof(Product));

    char deleteProductId[111];
    int flag;
    do
    {
        flag = 0;
        printf("\nEnter Product ID (Enter 0 to cancel): ");
        fgets(deleteProductId, sizeof(deleteProductId), stdin);
        deleteProductId[strcspn(deleteProductId, "\n")] = '\0';

        if (strcmp(deleteProductId, "0") == 0)
        {
            system("cls");
            printf("Operation cancelled.\n");
            return;
        }

        // kiểm tra độ dài
        if (strlen(deleteProductId) > 10)
        {
            printf("Product ID must be less than 10 characters!\n");
            flag = 1;
            continue;
        }
        // kiểm tra rỗng
        if (deleteProductId[0] == '\0')
        {
            printf("Product ID must not be empty!\n");
            flag = 1;
            continue;
        }

        int isExist = 0;
        for (int i = 0; i < productCount; i++)
        {
            if (strcmp(deleteProductId, products[i].productId) == 0)
            {
                isExist = 1;
                break;
            }
        }
        if (isExist == 0)
        {
            printf("Can't find Product!\n");
            flag = 1;
            continue;
        }
    } while (flag);

    printf("The product will be deleted: ");

    printf("\nProduct ID: %s", deleteProductId);
    printf("\nProduct Name: %s", products[0].productName);
    printf("\nQuantity: %d", products[0].quantity);
    printf("\nPrice: %d", products[0].price);
    printf("\n");

    printf("Are you sure you want to delete this product? (Y/N): ");
    char choice;
    scanf("%c", &choice);
    getchar();

    if (choice != 'Y' && choice != 'y')
    {
        printf("Product deletion cancelled.\n");
        return;
    }

    for (int i = 0; i < productCount; i++)
    {
        if (strcmp(deleteProductId, products[i].productId) == 0)
        {
            for (int j = i; j < productCount - 1; j++)
            {
                products[j] = products[j + 1];
            }
            productCount--;
            saveToFile("data/products.txt", products, productCount, sizeof(Product));
            break;
        }
    }

    printf("Product deleted successfully!\n");
    viewProducts();
}
void searchProduct()
{
    loadFromFile("data/products.txt", products, &productCount, sizeof(Product));
    int flag;
    char searchProductName[130];
    do
    {
        flag = 0;
        printf("Enter product name to search (Enter 0 to cancel): ");
        fgets(searchProductName, sizeof(searchProductName), stdin);
        searchProductName[strcspn(searchProductName, "\n")] = 0;

        if (strcmp(searchProductName, "0") == 0)
        {
            system("cls");
            printf("Operation cancelled.\n");
            return;
        }

        if (searchProductName[0] == '\0')
        {
            printf("Product name must not be empty!\n");
            flag = 1;
            continue;
        }

        if (strlen(searchProductName) > 30)
        {
            printf("Product name must be less than 30 characters!\n");
            flag = 1;
            continue;
        }

        int isExist = 0;
        for (int i = 0; i < productCount; i++)
        {
            if (strstr(products[i].productName, searchProductName))
            {
                isExist = 1;
                break;
            }
        }
        if (isExist == 0)
        {
            printf("Product not found!\n");
            flag = 1;
            continue;
        }

    } while (flag);

    printf("\n***** FIND PRODUCT BY NAME *****\n\n");
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
            printf("Enter Category ID (Enter 0 to cancel): ");
            scanf("%s", filterID);
            getchar();

            if (strcmp(filterID, "0") == 0)
            {
                system("cls");
                printf("Operation cancelled.\n");
                return;
            }

            int foundCategory = 0;
            printf("\n***** PRODUCTS *****\n\n");
            printf("|============|======================|==========|=========|\n");
            printf("| ID         | Name                 | Quantity | Price   |\n");
            printf("|------------|----------------------|----------|---------|\n");
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
            printf("Enter start price (Enter 0 to cancel): ");
            scanf("%lf", &startPrice);

            // printf("Nhập giá kết thúc: ");
            printf("Enter end price: ");
            scanf("%lf", &endPrice);

            if (startPrice > endPrice)
            {
                // printf("Khoảng giá vô lý!\n");
                printf("Invalid price range!\n");
                break;
            }
            printf("\n***** PRODUCTS *****\n\n");
            printf("|============|================================|==========|==========|\n");
            printf("| %-10s | %-30s | %8s | %8s |\n", "ID", "Product Name", "Quantity", "Price");
            printf("|============|================================|==========|==========|\n");
            for (int i = 0; i < productCount; i++)
            {
                if (products[i].price >= startPrice && products[i].price <= endPrice)
                {
                    printProduct(products[i]);
                    found = 1;
                    if (i == productCount - 1)
                        printf("|============|================================|==========|==========|\n");
                    else
                        printf("|------------|--------------------------------|----------|----------|\n");
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