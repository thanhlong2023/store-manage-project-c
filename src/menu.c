#include <stdio.h>
#include "../include/menu.h"
#include "../include/category.h"
#include "../include/product.h"
#include "../include/order.h"
#include "../include/file_utils.h"

void mainMenu()
{
    int choice;

    do
    {
        printf("\n***Student Management System Using C***\n\n");

        printCentered("CHOOSE YOUR ROLE");
        printf("========================================\n");
        // printf("[1]. Quản lý danh mục.\n");
        printf("[1]. Manage categories.\n");
        // printf("[2]. Quản lý sản phẩm.\n");
        printf("[2]. Manage products.\n");
        // printf("[3]. Quản lý đơn hàng.\n");
        printf("[3]. Manage orders.\n");
        // printf("[4]. Thoát.\n");
        printf("[4]. Exit.\n");
        printf("========================================\n");
        printf("Enter The Choice: ");
        scanf("%d", &choice);
        printf("\033[H\033[J");

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
            printf("Returning to the main menu...\n");
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    } while (choice != 4);
}

void categoryMenu()
{
    int choice;

    do
    {
        printf("\n***Student Management System Using C***\n\n");

        printCentered("CATEGORY MENU");
        printf("========================================\n");
        // printf("[1]. Xem danh sách danh mục.\n");
        printf("[1]. View categorie list.\n");
        // printf("[2]. Thêm danh mục.\n");
        printf("[2]. Add category.\n");
        // printf("[3]. Sửa danh mục.\n");
        printf("[3]. Update category.\n");
        // printf("[4]. Xóa danh mục.\n");
        printf("[4]. Delete category.\n");
        // printf("[5]. Tìm kiếm danh mục theo tên.\n");
        printf("[5]. Search category by name.\n");
        // printf("[6]. Sắp xếp danh mục theo tên.\n");
        printf("[6]. Sort category by name.\n");
        // printf("[0]. Quay lại.\n");
        printf("[0]. Back.\n");
        printf("========================================\n");
        printf("Enter The Choice: ");
        scanf("%d", &choice);
        getchar();
        printf("\033[H\033[J");
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
            // printf("\033[H\033[J");
            break;
        case 0:
            printf("Returning to the main menu...\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

void productMenu()
{
    int choice;

    do
    {
        printf("\n***Student Management System Using C***\n\n");

        printCentered("PRODUCT MENU");
        printf("========================================\n");
        // printf("[1]. Xem danh sách sản phẩm.\n");
        printf("[1]. View product list.\n");
        // printf("[2]. Thêm sản phẩm.\n");
        printf("[2]. Add product.\n");
        // printf("[3]. Sửa sản phẩm.\n");
        printf("[3]. Update product.\n");
        // printf("[4]. Xóa sản phẩm.\n");
        printf("[4]. Delete product.\n");
        // printf("[5]. Tìm kiếm sản phẩm theo tên.\n");
        printf("[5]. Search product by name.\n");
        // printf("[6]. Sắp xếp sản phẩm theo giá tiền.\n");
        printf("[6]. Sort product by price.\n");
        // printf("[7]. Lọc sản phẩm.\n");
        printf("[7]. Filter product.\n");
        // printf("[0]. Quay lại.\n");
        printf("[0]. Back.\n");
        printf("========================================\n");
        printf("Enter The Choice: ");
        scanf("%d", &choice);
        getchar();
        printf("\033[H\033[J");
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

            break;
        case 7:
            filterProduct();

            break;
        case 0:
            printf("Returning to the main menu...\n");
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    } while (choice != 0);
}

void orderMenu()
{
    int choice;

    do
    {
        printf("\n***Student Management System Using C***\n\n");
        printCentered("ORDER MENU");
        printf("========================================\n");
        // printf("[1]. Tạo đơn hàng.\n");
        printf("[1]. Create order.\n");
        printf("[2]. View order list.\n");
        printf("[3]. Back.\n");
        printf("========================================\n");
        printf("Enter The Choice: ");
        scanf("%d", &choice);
        getchar();
        printf("\033[H\033[J");
        switch (choice)
        {
        case 1:
            createOrder();

            break;
        case 2:
            viewOrders();

            break;
        case 3:
            printf("Returning to the main menu...\n");
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    } while (choice != 3);
}
