#include <stdio.h>
#include "../include/order.h"

Order orders[MAX_ORDERS];
int orderCount = 0;

void createOrder()
{
    if (orderCount >= MAX_ORDERS)
    {
        printf("Order list is full!\n");
        return;
    }

    Order newOrder;
    printf("Enter Order ID: ");
    scanf("%s", newOrder.orderId);
    printf("Enter Customer ID: ");
    scanf("%s", newOrder.customerId);
    printf("Enter Order Date (day month year): ");
    scanf("%d %d %d", &newOrder.date.day, &newOrder.date.month, &newOrder.date.year);

    // Nhập thông tin sản phẩm cho đơn hàng
    printf("Enter Product details for the order:\n");
    printf("Enter Product ID: ");
    scanf("%s", newOrder.product.productId);
    printf("Enter Product Name: ");
    scanf("%s", newOrder.product.productName);
    printf("Enter Quantity: ");
    scanf("%d", &newOrder.product.quantity);
    printf("Enter Price: ");
    scanf("%d", &newOrder.product.price);

    orders[orderCount++] = newOrder;
    printf("Order created successfully!\n");
}

void viewOrders()
{
    if (orderCount == 0)
    {
        printf("No orders available.\n");
        return;
    }

    printf("\n===== ORDERS =====\n");
    for (int i = 0; i < orderCount; i++)
    {
        printf("Order %d:\n", i + 1);
        printOrder(orders[i]);
    }
    printf("==================\n");
}

void printOrder(Order order)
{
    printf("Order ID: %s\n", order.orderId);
    printf("Customer ID: %s\n", order.customerId);
    printf("Order Date: ");
    printDate(order.date);
    printf("\nProduct Details:\n");
    printProduct(order.product);
}
