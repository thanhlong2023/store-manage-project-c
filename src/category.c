#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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
    printf("====================================================\n");
    printf("| %-10s | %-30s |\n", "ID", "Name");
    printf("====================================================\n");

    for (int i = 0; i < categoryCount; i++)
    {
        printf("| %-10s | %-30s |\n", categories[i].categoryId, categories[i].categoryName);
        if (i == categoryCount - 1)
            printf("====================================================\n");
        else
            printf("----------------------------------------------------\n");
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
    printf("===============================================\n");
    printf("| %-10s | %-30s |\n", "ID", "Name");
    printf("===============================================\n");
    for (int i = 0; i < categoryCount; i++)
    {
        printf("| %-10s | %-30s |\n", categories[i].categoryId, categories[i].categoryName);
        if (i == categoryCount - 1)
            printf("===============================================\n");
        else
            printf("-----------------------------------------------\n");
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

    // validate
    char newCategoryId[111], newCategoryName[131];
    int length;
    int flag;
    do
    {
        printf("\n");
        flag = 0;
        printf("Enter Category ID (Enter 0 to cancel): ");
        fgets(newCategoryId, sizeof(newCategoryId), stdin);
        newCategoryId[strcspn(newCategoryId, "\n")] = '\0';

        if (strcmp(newCategoryId, "0") == 0)
        {
            system("cls");
            printf("Operation cancelled.\n");
            return;
        }
        // kiem tra do dai
        if (strlen(newCategoryId) > 10)
        {
            printf("Category ID must be less than 10 characters!\n");
            flag = 1;
            continue;
        }

        // kiểm tra rỗng
        if (newCategoryId[0] == '\0')
        {
            printf("Category ID must not be empty!\n");
            flag = 1;
            continue;
        }

        // kiểm tra trùng id
        int isExitsId = 0;
        for (int i = 0; i < categoryCount; i++)
        {
            if (strcmp(newCategoryId, categories[i].categoryId) == 0)
            {
                printf("ID already exists. Please enter a different ID!\n");
                flag = 1;
                isExitsId = 1;
                break;
            }
        }
        if (isExitsId)
        {
            continue;
        }
    } while (flag);

    do
    {
        printf("\n");
        flag = 0;
        printf("Enter Category Name (Enter 0 to cancel): ");
        fgets(newCategoryName, sizeof(newCategoryName), stdin);
        newCategoryName[strlen(newCategoryName) - 1] = '\0';

        if (strcmp(newCategoryName, "0") == 0)
        {
            system("cls");
            printf("Operation cancelled.\n");
            return;
        }

        // kiểm tra do dai
        if (strlen(newCategoryName) > 30)
        {
            printf("Category Name must be less than 30 characters!\n");
            flag = 1;
            continue;
        }

        // kiểm tra rỗng
        if (newCategoryName[0] == '\0')
        {
            printf("Category Name must not be empty!\n");
            flag = 1;
            continue;
        }

        // kiểm tra trùng name
        int isExitsName = 0;
        for (int i = 0; i < categoryCount; i++)
        {
            if (strcmp(newCategoryName, categories[i].categoryName) == 0)
            {
                printf("Name already exists. Please enter a different name!\n");
                flag = 1;
                isExitsName = 1;
                break;
            }
        }
        if (isExitsName)
        {
            continue;
        }
    } while (flag);

    // gán giá trị cho
    Category newCategory;
    strcpy(newCategory.categoryId, newCategoryId);
    strcpy(newCategory.categoryName, newCategoryName);

    categories[categoryCount++] = newCategory;

    saveToFile("data/category.txt", categories, categoryCount, sizeof(Category));

    printf("Add category successfully!\n");
    printf("\n***** THE NEW CATEGORIE *****\n\n");
    printf("====================================================\n");
    printf("| %-10s | %-30s |\n", "ID", "Name");
    printf("====================================================\n");
    printf("| %-10s | %-30s |\n", newCategory.categoryId, newCategory.categoryName);
    printf("====================================================\n");

    pressEnterOrExit(1);
}
void updateCategory()
{
    loadFromFile("data/category.txt", categories, &categoryCount, sizeof(Category));

    char updateCategoryId[111];
    char updateCategoryName[131];
    int flag;

    do
    {
        flag = 0;
        printf("\nEnter Category ID (Enter 0 to cancel): ");
        fgets(updateCategoryId, sizeof(updateCategoryId), stdin);
        updateCategoryId[strcspn(updateCategoryId, "\n")] = '\0';

        if (strcmp(updateCategoryId, "0") == 0)
        {
            system("cls");
            printf("Operation cancelled.\n");
            return;
        }
        // kiểm tra độ dài
        if (strlen(updateCategoryId) > 10)
        {
            printf("Category ID must be less than 10 characters!\n");
            flag = 1;
            continue;
        }
        // kiểm tra rỗng
        if (updateCategoryId[0] == '\0')
        {
            printf("Category ID must not be empty!\n");
            flag = 1;
            continue;
        }
        // kiểm tra trùng id
        int isExistId = 0;
        for (int i = 0; i < categoryCount; i++)
        {
            if (strcmp(updateCategoryId, categories[i].categoryId) == 0)
            {
                isExistId = 1;
                break;
            }
        }
        if (!isExistId)
        {
            printf("Category ID do not exist! Please enter a different ID!\n");
            flag = 1;
            continue;
        }

    } while (flag);

    do
    {
        flag = 0;

        printf("\nEnter Category Name (Enter 0 to cancel): ");
        fgets(updateCategoryName, sizeof(updateCategoryName), stdin);
        updateCategoryName[strcspn(updateCategoryName, "\n")] = '\0';

        if (strcmp(updateCategoryName, "0") == 0)
        {
            system("cls");
            printf("Operation cancelled.\n");
            return;
        }
        // kiểm tra độ dài
        if (strlen(updateCategoryName) > 30)
        {
            printf("Category Name must be less than 30 characters!\n");
            flag = 1;
            continue;
        }
        // kiểm tra rỗng
        if (updateCategoryName[0] == '\0')
        {
            printf("Category Name must not be empty!\n");
            flag = 1;
            continue;
        }
        // kiểm tra trùng name
        int isExistName = 0;
        for (int i = 0; i < categoryCount; i++)
        {
            if (strcmp(updateCategoryName, categories[i].categoryName) == 0)
            {
                printf("Category Name already exists! Please enter a different name!\n");
                isExistName = 1;
                break;
            }
        }
        if (isExistName)
        {

            flag = 1;
            continue;
        }

        for (int i = 0; i < categoryCount; i++)
        {
            if (strcmp(updateCategoryId, categories[i].categoryId) == 0)
            {
                strcpy(categories[i].categoryName, updateCategoryName);

                saveToFile("data/category.txt", categories, categoryCount, sizeof(Category));
                printf("Update category successfully!\n");

                break;
            }
        }
    } while (flag);

    printf("\n***** THE NEW CATEGORIE *****\n\n");
    printf("====================================================\n");
    printf("| %-10s | %-30s |\n", "ID", "Name");
    printf("====================================================\n");
    printf("| %-10s | %-30s |\n", updateCategoryId, updateCategoryName);
    printf("====================================================\n");

    pressEnterOrExit(1);
}
void deleteCategory()
{
    loadFromFile("data/category.txt", categories, &categoryCount, sizeof(Category));
    loadFromFile("data/products.txt", productCopy, &productCountCopy, sizeof(Product));

    char deleteCategoryId[111];

    int flag;
    do
    {
        printf("\n");
        printf("Enter The Category ID (Enter 0 to cancel): ");
        fgets(deleteCategoryId, sizeof(deleteCategoryId), stdin);
        deleteCategoryId[strcspn(deleteCategoryId, "\n")] = '\0';

        flag = 0;

        if (strcmp(deleteCategoryId, "0") == 0)
        {
            system("cls");
            printf("Operation cancelled.\n");
            return;
        }
        // kiểm tra độ dài
        if (strlen(deleteCategoryId) > 10)
        {
            printf("Category ID must be less than 10 characters!\n");
            flag = 1;
            continue;
        }
        // kiểm tra rỗng
        if (deleteCategoryId[0] == '\0')
        {
            printf("Category ID must not be empty!\n");
            flag = 1;
            continue;
        }
        // kiểm tra id có tồn tại không
        int isExistId = 0;
        for (int i = 0; i < categoryCount; i++)
        {
            if (strcmp(deleteCategoryId, categories[i].categoryId) == 0)
            {
                isExistId = 1;
                break;
            }
        }
        if (!isExistId)
        {
            flag = 1;
            printf("Category ID do not exist! Please enter a different ID!\n");
            continue;
        }

    } while (flag);

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
        }
    }
}
void searchCategory()
{
    loadFromFile("data/category.txt", categories, &categoryCount, sizeof(Category));

    char searchCategoryName[131];

    int flag;
    do
    {
        printf("\n");
        printf("Enter Category Name (Enter 0 to cancel): ");
        fgets(searchCategoryName, sizeof(searchCategoryName), stdin);
        searchCategoryName[strcspn(searchCategoryName, "\n")] = '\0';

        flag = 0;

        if (strcmp(searchCategoryName, "0") == 0)
        {
            system("cls");
            printf("Operation cancelled.\n");
            return;
        }
        // kiểm tra độ dài
        if (strlen(searchCategoryName) > 30)
        {
            printf("Category Name must be less than 30 characters!\n");
            flag = 1;
            continue;
        }
        // kiểm tra rỗng
        if (searchCategoryName[0] == '\0')
        {
            printf("Category Name must not be empty!\n");
            flag = 1;
            continue;
        }
    } while (flag);

    printf("\n");
    printCentered("CATEGORY MENU");
    printf("================================================\n");
    printf("| %-10s | %-30s |\n", "ID", "Name");
    printf("================================================\n");

    int found = 0;
    for (int i = 0; i < categoryCount; i++)
    {
        if (strstr(categories[i].categoryName, searchCategoryName))
        {
            found = 1;
            printf("| %-10s | %-30s |\n", categories[i].categoryId, categories[i].categoryName);
            if (i == categoryCount - 1)
            {
                printf("================================================\n");
            }
            else
            {
                printf("------------------------------------------------\n");
            }
        }
    }
    if (!found)
    {
        printf("Category not found!\n");
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
        printf("================================================\n");
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