#include "items.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Item* item_array[NUM_ITEMS];

//adds item item_to_add to linked list "list"
void add_item(struct Item* item_to_add, struct Item** list) {
    if (*list == NULL) {
        //list is currently empty, make first item in linked list the item to add
        *list = item_to_add;
        return;
    }
    else {
        if (((*list)->next_item) == NULL) {
            (*list)->next_item = item_to_add;
        }
        else {
            add_item(item_to_add, &((*list)->next_item));
        }
    }
}

//drops item item_to_drop from linked list "list"
void drop_item(struct Item* item_to_drop, struct Item** list) {
    if (strcmp(item_to_drop->name, (*list)->name) == 0) {
        item_to_drop->next_item = NULL;
        *list = (*list)->next_item;
        return;
    }
    struct Item* temp_list = *list;
    while (temp_list != NULL && temp_list->next_item != NULL) {
        if (strcmp(item_to_drop->name, (*list)->next_item->name) == 0) {
            temp_list->next_item = temp_list->next_item->next_item;
            item_to_drop->next_item = NULL;
            break;
        }
        temp_list = temp_list->next_item; 
    }
}

//generates array of items with names
struct Item** generateItems() {
  for (int i = 0; i < NUM_ITEMS; i++) {
    item_array[i] = (struct Item *) malloc(sizeof(struct Item));
    switch(i) {
        case CANDLESTICK:
            item_array[i]->name = "candlestick";
            break;
        case DAGGER:
            item_array[i]->name = "dagger";
            break;
        case REVOLVER:
            item_array[i]->name = "revolver";
            break;
        case ROPE:
            item_array[i]->name = "rope";
            break;
        case LEAD_PIPE:
            item_array[i]->name = "lead pipe";
            break;
        case WRENCH:
            item_array[i]->name = "wrench";
            break;
    }
  }
  return &item_array;
}

