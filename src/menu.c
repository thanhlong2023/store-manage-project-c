#include <stdio.h>
#include "../include/menu.h"
#include "../include/category.h"
#include "../include/product.h"
#include "../include/order.h"

void mainMenu()
{
    int choice;

    do
    {
        printf("\n===== QUAN LY CUA HANG =====\n");
        printf("1. Quan ly danh muc\n");
        printf("2. Quan ly san pham\n");
        printf("3. Quan ly don hang\n");
        printf("4. Thoat\n");
        printf("============================\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            categoryMenu();
            break;
        case 2:
            productMenu();
            break;
        case 3:
            orderMenu();
            break;
        case 4:
            printf("Dang thoat chuong trinh...\n");
            break;
        default:
            printf("Lua chon khong hop le! Vui long nhap so tu 1 den 4.\n");
        }
    } while (choice != 4);
}

void categoryMenu()
{
    int choice;

    do
    {
        printf("\n===== QUAN LY DANH MUC =====\n");
        printf("1. Xem danh sach danh muc\n");
        printf("2. Them danh muc\n");
        printf("3. Sua danh muc\n");
        printf("4. Xoa danh muc\n");
        printf("5. Tim kiem danh muc theo ten\n");
        printf("6. Sap xep danh muc theo ten\n");
        printf("0. Quay lai menu chinh\n");
        printf("============================\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            displayCategories();
            break;
        case 2:
            addCategory();
            break;
        case 3:
            updateCategory();
            break;
        case 4:
            deleteCategory();
            break;
        case 5:
            searchCategory();
            break;
        case 6:
            sortCategory();
            break;
        case 0:
            printf("Quay lai menu chinh...\n");
            break;
        default:
            printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);
}

void productMenu()
{
    int choice;

    do
    {
        printf("\n===== QUAN LY SAN PHAM =====\n");
        printf("1. Xem danh sach san pham\n");
        printf("2. Them san pham\n");
        printf("3. Sua san pham\n");
        printf("4. Xoa san pham\n");
        printf("5. Tim kiem san pham theo ten\n");
        printf("6. Sap xep san pham theo gia tien\n");
        printf("7. Loc san pham\n");
        printf("0. Quay lai menu chinh\n");
        printf("============================\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            viewProducts();
            break;
        case 2:
            addProduct();
            break;
        case 3:
            updateProduct();
            break;
        case 4:
            deleteProduct();
            break;
        case 5:
            searchProduct();
            break;
        case 6:
            sortProduct();
        case 7:
            filterProduct();
        case 0:
            printf("Quay lai menu chinh...\n");
            break;
        default:
            printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);
}

void orderMenu()
{
    int choice;

    do
    {
        printf("\n===== QUAN LY DON HANG =====\n");
        printf("1. Tao don hang\n");
        printf("2. Xem danh sach don hang\n");
        printf("3. Quay lai menu chinh\n");
        printf("============================\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createOrder();
            break;
        case 2:
            viewOrders();
            break;
        case 3:
            printf("Quay lai menu chinh...\n");
            break;
        default:
            printf("Lua chon khong hop le! Vui long nhap so tu 1 den 3.\n");
        }
    } while (choice != 3);
}
