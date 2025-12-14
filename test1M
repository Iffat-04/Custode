#include <stdio.h>
#include "manage.c"   // your stock code file

/* ---------------------------------------------
   Test: Stock-In should increase quantity
   --------------------------------------------- */
int test_stock_in()
{
    Item item = {1, "Keyboard", 50};
    StockTransaction tx = {101, 1, STOCK_IN, 20};

    processStockTransaction(&item, &tx);

    int actual = item.quantity;
    int expected = 70;
    int success = actual == expected;

    printf("test_stock_in -> expected: %d, actual: %d, success: %d\n",
           expected, actual, success);

    return success;
}

/* ---------------------------------------------
   Test: Stock-Out with sufficient quantity
   --------------------------------------------- */
int test_stock_out_valid()
{
    Item item = {1, "Keyboard", 50};
    StockTransaction tx = {102, 1, STOCK_OUT, 30};

    processStockTransaction(&item, &tx);

    int actual = item.quantity;
    int expected = 20;
    int success = actual == expected;

    printf("test_stock_out_valid -> expected: %d, actual: %d, success: %d\n",
           expected, actual, success);

    return success;
}

/* ---------------------------------------------
   Test
