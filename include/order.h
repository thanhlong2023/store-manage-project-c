#ifndef ORDER_H
#define ORDER_H

#include "date.h"
#include "product.h"

#define MAX_ORDERS 100

typedef struct
{
    char orderId[10];
    char customerId[20];
    Date date;
    Product product; // Mỗi đơn hàng chứa 1 sản phẩm (có thể mở rộng sau)
} Order;

// Khai báo hàm xử lý Order
void createOrder();
void viewOrders();
void printOrder(Order order);

#endif
