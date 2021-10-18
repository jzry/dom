// All rights to @JZRY, Computer Science @ UCF
// --- Depth of market simulator ----

// This algorithm is designed to simulate a depth of market and extract statistics
// from the simulated intraday data. Input stream may be changed, but the default is for showcase.

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <math.h>
#include <new>
#include <iostream>

#define DEBUG 0
#define TRUE 1
#define MAX_RAND_VAL 30

// Divide the number of market orders by half.
int *orderSplit(int numOfOrders)
{
    int *orderBatch, i = 0, sum = 0, order;

    // Holder for the division of the orders.
    // orderBatch = malloc(sizeof(int) * 2);
    orderBatch = new int[2];

    if (numOfOrders % 2 == 0)
    {
        sum += (numOfOrders / 2);

        // Sets the order batch size by dividing the number of total orders in half.
        orderBatch[0] = sum;
        orderBatch[1] = sum;
    }
    else
    {
        sum += (numOfOrders / 2);

        // Generate either a 0 or 1 for order variation.
        order = rand() % 2;

        if (DEBUG == 1)
        {
            printf("RANDOM NUMBER: %d\n", order);
        }

        // Sets the order batch size by dividing the number of total orders in half.
        if (order == 1)
        {
            orderBatch[0] = sum + 1;
            orderBatch[1] = sum;
        }
        else
        {
            orderBatch[0] = sum;
            orderBatch[1] = sum + 1;
        }
    }

    return orderBatch;
}

// Uses C's built-in qsort() function to sort given arrays.
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// Create and return a sorted array of n random float
// representing a series of buy or sell orders.
int *generateOrders(int n)
{
    int *array = new int[n];
    int i;

    for (i = 0; i < n; i++)
    {
        array[i] = rand() % MAX_RAND_VAL + 1;
    }

    // Sorts arrays using C's quicksort.
    qsort(array, n, sizeof(int), compare);

    return array;
}

// Print the data and statistics.
void printStatistics(int *buy_orders, int *sell_orders, int buy_amount, int sell_amount)
{
    float avg_ask, avg_buy, buy_sum, sell_sum;
    int i;

    printf("-- ORDERS --\n\n");
    printf("Buy orders: \n\n");

    // Print the first order batch.
    for (i = 0; i < buy_amount; i++)
    {
        printf("%d%c", buy_orders[i], (i == buy_amount - 1) ? '\n' : ' ');
        buy_sum += buy_orders[i];
    }

    printf("\nSell orders: \n\n");

    // Print the second order batch.
    for (i = 0; i < sell_amount; i++)
    {
        printf("%d%c", sell_orders[i], (i == sell_amount - 1) ? '\n' : ' ');
        sell_sum += sell_orders[i];
    }

    printf("\n\n");

    // Summary of market.
    printf("-- SUMMARY --\n\n");
    printf("Average ask price: %.02f$\n", buy_sum / buy_amount);
    printf("Average bid price: %.02f$\n", sell_sum / sell_amount);
    printf("Average bid-ask spread: %.2f$\n", fabsf((buy_sum / buy_amount) - (sell_sum / sell_amount)));
    printf("Notional ask value: %.02f$\n", buy_sum);
    printf("Notional bid value: %.02f$\n", sell_sum);
    printf("Number of buy orders: %d\n", buy_amount);
    printf("Number of sell orders: %d\n", sell_amount);
    printf("\n\n");
}

// Simulate a depth of market with a given amount of market orders.
void simulateOrderFlow(int numOfOrders)
{
    int i, *orderBatchSize, *buy_orders, *sell_orders;

    if (numOfOrders < 2)
    {
        printf("Not enough orders given! Must input more than 1 order.\n");
        return;
    }

    // Split up the total number of orders in roughly half.
    orderBatchSize = orderSplit(numOfOrders);

    if (DEBUG == 1)
    {
        for (i = 0; i < 2; i++)
        {
            printf("orderBatchSize[%d]: %d\n", i, orderBatchSize[i]);
        }
    }

    // Make half of the orders randomly generate above the ask price.
    buy_orders = generateOrders(orderBatchSize[0]);

    // Make half of the orders randomly generate below the ask price.
    sell_orders = generateOrders(orderBatchSize[1]);

    // Print statistics about the simulated depth of market.
    printStatistics(buy_orders, sell_orders, orderBatchSize[0], orderBatchSize[1]);

    delete(orderBatchSize);
    free(buy_orders);
    free(sell_orders);

    return;
}

// Main driver function.
int main(int argc, char **argv)
{
    int numOfOrders;

    if (argc < 2)
    {
        printf("Proper syntax is '%s (number of orders)'\n", argv[0]);
    }

    srand(time(NULL));
    numOfOrders = atoi(argv[1]);

    // Switch DEBUG variable at the top of the program file to 0 to place orders.
    if (DEBUG == 0)
    {
        printf("\n\nSimulating the depth of market with %d orders...\n\n", numOfOrders);

        simulateOrderFlow(numOfOrders);
    }

    return 0;
}
