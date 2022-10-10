#ifndef ITEMS_H
#define ITEMS_H

#include <stdio.h>

#define CANDLESTICK 0
#define DAGGER 1
#define REVOLVER 2
#define ROPE 3
#define LEAD_PIPE 4
#define WRENCH 5

#define NUM_ITEMS 6

struct Item {
    char* name;
    //used for implementing a linked list of items
    struct Item* next_item;
};


void add_item(struct Item*, struct Item**);

void drop_item(struct Item*,  struct Item**);

struct Item** generateItems();

#endif