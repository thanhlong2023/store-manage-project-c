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
    Product product;
} Order;

#endif
