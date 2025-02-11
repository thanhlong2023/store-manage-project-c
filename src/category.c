#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/category.h"
#include "../include/file_utils.h"

Category categories[MAX_CATEGORIES];
int categoryCount = 0;

void displayCategories()
{
    loadCategoriesFromFile("data/category.txt", categories, &categoryCount);
    if (categoryCount == 0)
    {
        printf("Danh muc trong.\n");
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
    if (categoryCount >= MAX_CATEGORIES)
    {
        printf("Danh sach danh muc da day!\n");
        return;
    }

    // kiểm tra trùng nhau
    char newCategoryId[10], newCategoryName[30];
    printf("Nhap Category ID: ");
    scanf("%s", newCategoryId);
    getchar();
    printf("Nhap Category Name: ");
    fgets(newCategoryName, sizeof(newCategoryName), stdin);
    newCategoryName[strlen(newCategoryName) - 1] = '\0'; // Xóa ki tự \n

    for (int i = 0; i < categoryCount; i++)
    {
        if (strcmp(newCategoryId, categories[i].categoryId) == 0)
        {
            printf("ID da ton tai!\n");
            return;
        }
        if (strcmp(newCategoryName, categories[i].categoryName) == 0)
        {
            printf("Ten da ton tai!\n");
            return;
        }
    }

    // gán giá trị cho
    Category newCategory;
    strcpy(newCategory.categoryId, newCategoryId);
    strcpy(newCategory.categoryName, newCategoryName);

    categories[categoryCount++] = newCategory;
    printf("Them danh muc thanh cong!\n");

    saveCategoriesToFile("data/category.txt", categories, categoryCount);
}
void updateCategory()
{
    char updateCategoryId[10];
    printf("Nhap Category ID: ");
    scanf("%s", updateCategoryId);
    getchar();

    for (int i = 0; i < categoryCount; i++)
    {
        if (strcmp(updateCategoryId, categories[i].categoryId) == 0)
        {
            char newCategoryName[30];
            printf("Nhap Category Name: ");
            fgets(newCategoryName, sizeof(newCategoryName), stdin);
            newCategoryName[strlen(newCategoryName) - 1] = '\0';

            strcpy(categories[i].categoryName, newCategoryName);
            printf("Cap nhat danh muc thanh cong!\n");

            saveCategoriesToFile("data/category.txt", categories, categoryCount);
            return;
        }
    }
    printf("ID khong ton tai!\n");
    return;
}
void deleteCategory()
{
    char deleteCategoryId[10];
    printf("Nhap Category ID: ");
    scanf("%s", deleteCategoryId);
    getchar();

    for (int i = 0; i < categoryCount; i++)
    {
        if (strcmp(deleteCategoryId, categories[i].categoryId) == 0)
        {
            for (int j = i; j < categoryCount - 1; j++)
            {
                categories[j] = categories[j + 1];
            }
            categoryCount--;
            printf("Xoa danh muc thanh cong!\n");

            saveCategoriesToFile("data/category.txt", categories, categoryCount);
            return;
        }
    }
}
void searchCategory()
{
    char searchCategoryName[30];
    printf("Nhap Category Name: ");
    fgets(searchCategoryName, sizeof(searchCategoryName), stdin);
    searchCategoryName[strlen(searchCategoryName) - 1] = '\0';

    for (int i = 0; i < categoryCount; i++)
    {
        if (strcmp(searchCategoryName, categories[i].categoryName) == 0)
        {
            printf("ID: %s, Name: %s\n", categories[i].categoryId, categories[i].categoryName);
            return;
        }
    }
}

void sortCategory()
{
    int choice;
    do
    {
        printf("\n===== SAP XEP DANH MUC =====\n");
        printf("1. Sap xep tang dan\n");
        printf("2. Sap xep giam dan\n");
        printf("0. Quay lai\n");
        printf("============================\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
        {
            qsort(categories, categoryCount, sizeof(Category), cmpAscName);
            printf("Sap xep thanh cong!\n");

            saveCategoriesToFile("data/category.txt", categories, categoryCount);
            choice = 0;
            break;
        }
        case 2:
        {
            qsort(categories, categoryCount, sizeof(Category), cmpDescName);
            printf("Sap xep thanh cong!\n");

            saveCategoriesToFile("data/category.txt", categories, categoryCount);
            choice = 0;
            break;
        }
        case 0:
        {
            break;
        }
        default:
        {
            printf("Lua chon khong hop le!\n");
            break;
        }
        }
    } while (choice != 0);
}