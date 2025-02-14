#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/category.h"
#include "../include/file_utils.h"
#include "../include/product.h"

Category categories[MAX_CATEGORIES];
int categoryCount = 0;

Product productCopy[MAX_PRODUCTS];
int productCountCopy = 0;

void displayCategories()
{
    loadFromFile("data/category.txt", categories, &categoryCount, sizeof(Category));

    if (categoryCount == 0)
    {
        // printf("Danh muc trong.\n");
        printf("Category list is empty.\n");
        return;
    }
    printf("\n***** CATEGORIES *****\n\n");
    printf("|=====|============|\n");
    printf("| %-3s | %-10s |\n", "ID", "Name");
    printf("|=====|============|\n");

    for (int i = 0; i < categoryCount; i++)
    {
        printf("| %-3s | %-10s |\n", categories[i].categoryId, categories[i].categoryName);
        if (i == categoryCount - 1)
            printf("|=====|============|\n");
        else
            printf("|-----|------------|\n");
    }
    pressEnterOrExit(1);
}
void displayCategoriesNotPress()
{
    loadFromFile("data/category.txt", categories, &categoryCount, sizeof(Category));

    if (categoryCount == 0)
    {
        // printf("Danh muc trong.\n");
        printf("Category list is empty.\n");
        return;
    }
    printf("\n***** CATEGORIES *****\n\n");
    printf("|=====|============|\n");
    printf("| %-3s | %-10s |\n", "ID", "Name");
    printf("|=====|============|\n");

    for (int i = 0; i < categoryCount; i++)
    {
        printf("| %-3s | %-10s |\n", categories[i].categoryId, categories[i].categoryName);
        if (i == categoryCount - 1)
            printf("|=====|============|\n");
        else
            printf("|-----|------------|\n");
    }
}
void addCategory()
{
    loadFromFile("data/category.txt", categories, &categoryCount, sizeof(Category));

    if (categoryCount >= MAX_CATEGORIES)
    {
        printf("Category List is full!\n");
        return;
    }

    // kiểm tra trùng nhau
    char newCategoryId[10], newCategoryName[30];
    // printf("Nhập Category ID: ");
    printf("Enter Category ID: ");
    scanf("%s", newCategoryId);
    getchar();
    // printf("Nhập Category Name: ");
    printf("Enter Category Name: ");
    fgets(newCategoryName, sizeof(newCategoryName), stdin);
    newCategoryName[strlen(newCategoryName) - 1] = '\0'; // Xóa ki tự \n

    for (int i = 0; i < categoryCount; i++)
    {
        if (strcmp(newCategoryId, categories[i].categoryId) == 0)
        {
            // printf("ID đã tồn tại. Vui lòng nhập ID khác!\n");
            printf("ID already exists. Please enter a different ID!\n");
            return;
        }
        if (strcmp(newCategoryName, categories[i].categoryName) == 0)
        {
            // printf("Tên đã tồn tại. Vui lòng nhập tên khác!\n");
            printf("Name already exists. Please enter a different name!\n");
            return;
        }
    }

    // gán giá trị cho
    Category newCategory;
    strcpy(newCategory.categoryId, newCategoryId);
    strcpy(newCategory.categoryName, newCategoryName);

    categories[categoryCount++] = newCategory;
    // printf("Thêm danh mục thành công!\n");
    printf("Add category successfully!\n");

    saveToFile("data/category.txt", categories, categoryCount, sizeof(Category));

    displayCategories();
}
void updateCategory()
{
    loadFromFile("data/category.txt", categories, &categoryCount, sizeof(Category));

    char updateCategoryId[10];
    printf("Enter Category ID: ");
    scanf("%s", updateCategoryId);
    getchar();

    for (int i = 0; i < categoryCount; i++)
    {
        if (strcmp(updateCategoryId, categories[i].categoryId) == 0)
        {
            char newCategoryName[30];
            printf("Enter Category Name: ");
            fgets(newCategoryName, sizeof(newCategoryName), stdin);
            newCategoryName[strlen(newCategoryName) - 1] = '\0';

            strcpy(categories[i].categoryName, newCategoryName);
            // printf("Cap nhat danh muc thanh cong!\n");
            printf("Update category successfully!\n");

            saveToFile("data/category.txt", categories, categoryCount, sizeof(Category));

            displayCategories();

            return;
        }
    }
    // printf("ID khong ton tai!\n");
    printf("ID not found!\n");
    return;
}
void deleteCategory()
{
    // loadFromFile("data/category.txt", categories, &categoryCount, sizeof(Category));
    loadFromFile("data/products.txt", productCopy, &productCountCopy, sizeof(Product));

    char deleteCategoryId[10];
    printf("Enter The Category ID: ");
    scanf("%s", deleteCategoryId);
    getchar();

    for (int i = 0; i < categoryCount; i++)
    {
        if (strcmp(deleteCategoryId, categories[i].categoryId) == 0)
        {
            printf("One Category Found for ID: %s\n", deleteCategoryId);
            printf("------------------------------------\n");
            printf("Category ID: %s\n", categories[i].categoryId);
            printf("Category Name: %s\n", categories[i].categoryName);

            printf("\nAre you sure you want to delete this category? (Y/N): ");
            char confirm;
            scanf("%c", &confirm);
            getchar();

            if (confirm != 'Y' && confirm != 'y')
            {
                // printf("Huy xoa danh muc!\n");
                printf("Delete category canceled!\n");
                return;
            }
            for (int j = i; j < categoryCount - 1; j++)
            {
                categories[j] = categories[j + 1];
            }
            categoryCount--;
            // printf("Xoa danh muc thanh cong!\n");
            printf("Delete category successfully!\n");

            saveToFile("data/category.txt", categories, categoryCount, sizeof(Category));

            int newProductCount = 0;
            // xóa toàn bộ sản phẩm thuộc danh mục
            for (int i = 0; i < productCountCopy; i++)
            {
                if (strcmp(deleteCategoryId, productCopy[i].categoryId) != 0)
                {
                    productCopy[newProductCount] = productCopy[i];
                    newProductCount++;
                }
            }
            productCountCopy = newProductCount;
            saveToFile("data/products.txt", productCopy, productCountCopy, sizeof(Product));

            displayCategories();
            return;
        }
    }
    // printf("Không tìm thấy danh mục.\n");
    printf("No category found!\n");
}
void searchCategory()
{
    loadFromFile("data/category.txt", categories, &categoryCount, sizeof(Category));
    char searchCategoryName[30];
    printf("Enter Category Name: ");
    fgets(searchCategoryName, sizeof(searchCategoryName), stdin);
    searchCategoryName[strcspn(searchCategoryName, "\n")] = '\0';

    printf("\n");
    printCentered("CATEGORY MENU");
    printf("================================\n");
    printf("| %-5s | %-20s |\n", "ID", "Name");
    printf("================================\n");

    int found = 0;
    for (int i = 0; i < categoryCount; i++)
    {
        if (strstr(categories[i].categoryName, searchCategoryName))
        {
            printf("| %-5s | %-20s |\n", categories[i].categoryId, categories[i].categoryName);
            found = 1;
            if (i == categoryCount - 1)
            {
                printf("=================================\n");
            }
            else
            {
                printf("--------------------------------\n");
            }
        }
    }

    if (!found)
    {
        printf("No category found!\n");
    }

    pressEnterOrExit(1);
}

void sortCategory()
{
    loadFromFile("data/category.txt", categories, &categoryCount, sizeof(Category));

    int choice;
    do
    {
        // printf("\n===== SAP XEP DANH MUC =====\n");
        printCentered("\nSORT CATEGORY\n");
        // printf("1. Sap xep tang dan\n");
        printf("[1]. Sort category in ascending order.\n");
        // printf("2. Sap xep giam dan\n");
        printf("[2]. Sort category in descending order.\n");
        printf("[0]. Back.\n");
        printf("============================\n");
        // printf("Nhap lua chon cua ban: ");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        printf("\033[H\033[J");

        switch (choice)
        {
        case 1:
        {
            qsort(categories, categoryCount, sizeof(Category), cmpAscName);
            // printf("Sap xep thanh cong!\n");
            printf("Sort category successfully!\n");

            saveToFile("data/category.txt", categories, categoryCount, sizeof(Category));

            displayCategories();

            choice = 0;
            break;
        }
        case 2:
        {
            qsort(categories, categoryCount, sizeof(Category), cmpDescName);
            // printf("Sap xep thanh cong!\n");
            printf("Sort category successfully!\n");

            saveToFile("data/category.txt", categories, categoryCount, sizeof(Category));

            displayCategories();

            choice = 0;
            break;
        }
        case 0:
        {
            break;
        }
        default:
        {
            // printf("Lua chon khong hop le!\n");
            printf("Invalid choice!\n");
            break;
        }
        }
    } while (choice != 0);
}