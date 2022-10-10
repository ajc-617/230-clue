#include <stdio.h>
#include <stdlib.h>
#include "rooms.h"
#include "items.h"
#include "avatar.h"
#include <time.h>
#include <stdbool.h>
#include <string.h>

struct Room** rooms_arr;
struct Item** items_arr;

//function for freeing up memory space
void free_memory() {
    for (int i = 0; i < NUM_ROOMS; i++) {
        free(rooms_arr[i]);
    }
    for (int i = 0; i < NUM_ITEMS; i++) {
        free(items_arr[i]);
    }
} 

int main() {
    //initialize player avatar struct
    struct Avatar* avatar;
    avatar = (struct Avatar*) malloc(sizeof(struct Avatar));

    //first, randomly determine which room will be in which location with fisher yates
    //rooms will be: kitchen, bedroom 1, bedroom 2, dining room, rec room, family room
    rooms_arr = generateRooms();

    //characters: miss peacock, colonel mustard, professor plum, miss scarlett, mr green
    char* characters[NUM_CHARACTERS] = {"miss peacock", "colonel musard", "professor plum", "miss scarlett", "mr green"};
    char* items[NUM_ITEMS] = {"candlestick", "dagger", "revolver", "rope", "lead pipe", "wrench"};
    char* rooms[NUM_ROOMS] = {"study", "library", "billiard room", "conservatory", "hall", "ball room", "lounge", "dining room", "kitchen"};

    srand(time(0));
    //randomly select item, room, character of interest as well as avatar starting location
    int correct_item = rand() % NUM_ITEMS;
    int correct_character = rand() % NUM_CHARACTERS;
    int correct_room = rand() % NUM_ROOMS;
    int avatar_room = rand() % NUM_ROOMS;
    //randomly select which rooms will contain the 6 items (as each room can only have 1 item max at the start) and
    //which items will be in which room

    items_arr = generateItems();

    //first step is to shuffle up this array: first 6 elements will be indices of rooms in rooms_arr which will have items
    int rooms_with_items[9] = {0,1,2,3,4,5,6,7,8};
    for (int i = NUM_ROOMS - 1; i > 0; i--) {
        int j = rand() % (i+1);
        int	temp = rooms_with_items[j];
        rooms_with_items[j] = rooms_with_items[i];
        rooms_with_items[i] = temp;
    }

    /*now the first six indices of rooms_with_items will be the indices of the rooms in rooms_arr which will
    have items.
    Index 0 in rooms_with_items will be room with candlestick,
    Index 1 in rooms_with_tems will be room with dagger,
    Index 2 in rooms_with_items will be room with revolver,
    Index 3 in rooms_with_items will be room with rope
    Index 4 in rooms_with_items will be room with lead pipe
    Index 5 in rooms_with_items will be room with wrench
    */
    
    for (int i = 0; i < NUM_ITEMS; i++) {
        add_item(items_arr[i], &(rooms_arr[rooms_with_items[i]]->itemList));
    }

    //shuffle up character locations with fisher yates shuffle
    int rooms_with_characters[9] = {0,1,2,3,4,5,6,7,8};
    for (int i = NUM_ROOMS - 1; i > 0; i--) {
        int j = rand() % (i+1);
        int	temp = rooms_with_items[j];
        rooms_with_items[j] = rooms_with_items[i];
        rooms_with_items[i] = temp;
    }

    //randomly puts characters in rooms
    for (int i = 0; i < NUM_CHARACTERS; ++i) {
        rooms_arr[rooms_with_characters[i]]->characters[i] = true;
    }

    //randomly give avatar starting location
    avatar->location = rooms_arr[avatar_room];
    int clue_uses = 0;

    bool running = true;
    while (running) {
        printf("enter a command:\n");
        char *buffer = NULL;
        size_t bufsize;
        size_t num_characters;
        num_characters = getline(&buffer, &bufsize, stdin);
        buffer[num_characters-1] = 0;
        //help command helps with user commands, gives info on each command
        if (strcmp(buffer, "help") == 0) {
            char *buffer_2 = NULL;
            size_t bufsize_2;
            size_t num_characters_2;
            num_characters_2 = getline(&buffer_2, &bufsize_2, stdin);
            buffer_2[num_characters_2-1] = 0;
            if (strcmp(buffer_2, "list") == 0) {
                printf("the list command will print out all of the items, characters, and rooms in the game\n");
            }
            if (strcmp(buffer_2, "look") == 0) {
                printf("the look command will print out all of the items in the same room as the player, all of the characters in the same room as the player, and the rooms to the east, west, north, and south of the player (if they exist)\n");
            }
            if (strcmp(buffer_2, "go") == 0) {
                printf("to use the go command, first type \"go\" and then type the direction you wish to move, either \"east\", \"west\", \"south\", or \"north\"\n");
            }
            if (strcmp(buffer_2, "take") == 0) {
                printf("to use the take command, type \"take\" and then type the item you wish to take from the room you are in\n");
            }
            if (strcmp(buffer_2, "drop") == 0) {
                printf("to use the drop command, type \"drop\" and then type the item from your inventory you wish to drop from your inventory into the room you are currently in\n");
            }
            if (strcmp(buffer_2, "inventory") == 0) {
                printf("the inventory command will list all of the items in your inventory\n");
            }
            if (strcmp(buffer_2, "clue") == 0) {
                printf("to use the clue command, type \"clue\" and then type a character you wish to bring into the room (case sensitive). You will then be notified of a character match if the character of interest is in the same room as you, an item match if you have the item of interest in your inventory, or it is in the same room as you, or a room match if you are in the room of interest.\n");
            }
        }
        //list out rooms, items, characters
        if (strcmp(buffer, "list") == 0) {
            printf("List of rooms:\n");
            for (int i = 0; i < NUM_ROOMS; i++) {
                printf("%s\n", rooms_arr[i]->name);
            }
            printf("List of characters:\n");
            for(int i = 0; i < NUM_CHARACTERS; i++) {
                printf("%s\n", characters[i]);
            }
            printf("List of items:\n");
            for (int i = 0; i < NUM_ITEMS; i++) {
                printf("%s\n", items[i]);
            }
        }
        //displays items, characters, bordering rooms
        if (strcmp(buffer, "look") == 0) {
            printf("Current room: %s \n", avatar->location->name);
            printf("Characters in this room: \n");
            for (int i = 0; i < NUM_CHARACTERS; i++) {
                if (avatar->location->characters[i] == true) {
                    printf("%s\n", characters[i]);
                }
            }
            printf("items in this room:\n");
            struct Item* cur_room_list = avatar->location->itemList;
            if (cur_room_list == NULL) {
                printf("there are no items items in this room\n");
            }
            while (cur_room_list != NULL) {
                printf("%s\n", cur_room_list->name);
                cur_room_list = cur_room_list->next_item;
            } 
            printf("rooms in each direction:\n");
            if (avatar->location->East != NULL) {
                printf("Room to the East: %s\n", avatar->location->East->name);
            }
            else {
                printf("There is no room the the East\n");
            }
            if (avatar->location->West != NULL) {
                printf("Room to the West: %s\n", avatar->location->West->name);
            }
            else {
                printf("There is no room to the West\n");
            }
            if (avatar->location->South != NULL) {
                printf("Room to the South: %s\n", avatar->location->South->name);
            }
            else {
               printf("There is no room to the South\n"); 
            }
            if (avatar->location->North != NULL) {
                printf("Room to the North: %s\n", avatar->location->North->name);
            }
            else {
                printf("There is no room to the North\n");
            }
        }
        //type go, type either "east", "west", "south", or "north" to go in that direction. If direction is invalid, reprompt user for a valid direction
        if (strcmp(buffer, "go") == 0) {
            char *buffer_2 = NULL;
            size_t bufsize_2;
            size_t num_characters_2;
            while (true) {
                printf("Enter a direction: east, west, south, or north:\n");
                num_characters_2 = getline(&buffer_2, &bufsize_2, stdin);
                buffer_2[num_characters_2-1] = 0;
                //if player doesn't input a valid direction, prompt them again for another direction
                if (!(strcmp(buffer_2, "east") == 0 || strcmp(buffer_2, "west") == 0 || strcmp(buffer_2, "south") == 0 || strcmp(buffer_2, "north") == 0)) {
                    printf("invalid direction, try again.\n");
                    continue;
                }
                if (strcmp(buffer_2, "east") == 0) {
                    //east is invalid
                    if (avatar->location->East == NULL) {
                        printf("There is no room to the east of the current room, try again\n");
                        continue;
                    }
                    //east is valid, move player to that room
                    else {
                        printf("moving to %s\n", avatar->location->East->name);
                        avatar->location = avatar->location->East;
                        break;
                    }
                }
                if (strcmp(buffer_2, "west") == 0) {
                    //west is invalid
                    if (avatar->location->West == NULL) {
                        printf("There is no room to the west of the current room, try again\n");
                        continue;
                    }
                    //west is valid, move player to that room
                    else {
                        printf("moving to %s\n", avatar->location->West->name);
                        avatar->location = avatar->location->West;
                        break;
                    }
                }
                if (strcmp(buffer_2, "south") == 0) {
                    //south is invalid
                    if (avatar->location->South == NULL) {
                        printf("There is no room to the south of the current room, try again\n");
                        continue;
                    }
                    //south is valid, move player to that room
                    else {
                        printf("moving to %s\n", avatar->location->South->name);
                        avatar->location = avatar->location->South;
                        break;
                    }
                }
                if (strcmp(buffer_2, "north") == 0) {
                    //north is invalid
                    if (avatar->location->North == NULL) {
                        printf("There is no room to the north of the current room, try again\n");
                        continue;
                    }
                    //north is valid, move player to that room
                    else {
                        printf("moving to %s\n", avatar->location->North->name);
                        avatar->location = avatar->location->North;
                        break;
                        num_characters_2 = getline(&buffer_2, &bufsize_2, stdin);
                        buffer_2[num_characters_2-1] = 0;
                    }
                }

            }
        }
        //user types take, hits enter, types item they want to take
        if (strcmp(buffer, "take") == 0) {
            struct Item* cur_room_items = avatar->location->itemList;
            if (cur_room_items == NULL) {
                printf("There are no items to take in this room, type in another command\n");
                //ask for another command, as take command is invalid
                continue;
            }
            int item_picked = 0;
            while(item_picked == 0) {
                printf("input an time to take from the current room:\n");
                char *buffer_2 = NULL;
                size_t bufsize_2;
                size_t num_characters_2;
                num_characters_2 = getline(&buffer_2, &bufsize_2, stdin);
                buffer_2[num_characters_2-1] = 0;
                do { 
                    if (strcmp(cur_room_items->name, buffer_2) == 0) {
                        printf("taking item %s from room %s\n", cur_room_items->name, avatar->location->name);
                        //remove item from room
                        drop_item(cur_room_items, &(avatar->location->itemList));
                        //add item to player inventory
                        add_item(cur_room_items, &(avatar->inventory));
                        item_picked = 1;
                        break;
                    }
                    cur_room_items = cur_room_items->next_item;
                } while(cur_room_items != NULL);
                if (item_picked == 0) {
                    printf("item picked was invalid, try again\n");
                }
            } 
        }
        //user types drop, enters item they want to drop
        if (strcmp(buffer, "drop") == 0) {
            struct Item* cur_inventory = avatar->inventory;
            if (avatar->inventory == NULL) {
                printf("no items in player inventory to drop, try another command\n");
                continue;
            }
            int item_picked = 0;
            while(item_picked == 0) {
                printf("input an time to drop from inventory:\n");
                char *buffer_2 = NULL;
                size_t bufsize_2;
                size_t num_characters_2;
                num_characters_2 = getline(&buffer_2, &bufsize_2, stdin);
                buffer_2[num_characters_2-1] = 0;
                do { 
                    if (strcmp(cur_inventory->name, buffer_2) == 0) {
                        printf("dropping item %s\n", cur_inventory->name);
                        //remove item from player inventory
                        drop_item(cur_inventory, &(avatar->inventory));
                        //add item to current room
                        add_item(cur_inventory, &(avatar->location->itemList));
                        item_picked = 1;
                        break;
                    }
                    cur_inventory = cur_inventory->next_item;
                } while(cur_inventory != NULL);
                if (item_picked == 0) {
                    printf("item picked was invalid, try again\n");
                }
            } 
        }
        //lists items in player inventory
        if (strcmp(buffer, "inventory") == 0) {
            struct Item* cur_inventory = avatar->inventory;
            printf("items in inventory:\n");
            if (cur_inventory == NULL) {
                printf("player currently has no items in inventory\n");
                continue;
            }
            while (cur_inventory != NULL) {
                printf("%s\n", cur_inventory->name);
                cur_inventory = cur_inventory->next_item;
            }
        }
        if (strcmp(buffer, "clue") == 0) {
            clue_uses++;
            //char* characters[NUM_CHARACTERS] = {"miss peacock", "colonel musard", "professor plum", "miss scarlett", "mr green"};
            int valid = 0;
            char* character_to_move;
            int index_of_character;
            do {
                printf("input a character name:\n");
                char *buffer_2 = NULL;
                size_t bufsize_2;
                size_t num_characters_2;
                num_characters_2 = getline(&buffer_2, &bufsize_2, stdin);
                buffer_2[num_characters_2-1] = 0;
                for (int i = 0; i < NUM_CHARACTERS; i++) {
                    if (strcmp(buffer_2, characters[i]) == 0) {
                        character_to_move = characters[i];
                        index_of_character = i;
                        valid = 1;
                        break;
                    }
                }
                if (valid == 0) {
                    printf("invalid character to move, re-enter a valid character\n");
                }
            } while (valid == 0);
            for (int i = 0; i < NUM_ROOMS; i++) {
                //remove character that player input from the room they are currently in
                if (rooms_arr[i]->characters[index_of_character] == true) {
                    rooms_arr[i]->characters[index_of_character] = false;
                    break;
                }
            }
            //move character to the room the player is in
            avatar->location->characters[index_of_character] = true;
            bool room_match = false;
            bool item_match = false;
            bool character_match = false;
            //if player is in same room as room of interest, they have a room match
            if (strcmp(avatar->location->name, rooms[correct_room]) == 0) {
                printf("Room match\n");
                room_match = true;
            }
            //If player is in the same room as character of interest, they have a character match
            if (avatar->location->characters[index_of_character] == true) {
                printf("Character match\n");
                character_match = true;
            }
            //If player has the item of interest in their inventory or if they are in the same room as the item, they have an item match
            struct Item* cur_inventory = avatar->inventory;
            while (cur_inventory != NULL) {
                if (strcmp(cur_inventory->name, items[correct_item]) == 0) {
                    printf("Item match\n");
                    item_match = true;
                    break;
                }
                cur_inventory = cur_inventory->next_item;
            }
            struct Item* cur_item = avatar->location->itemList;
            while (cur_item != NULL) {
                if (strcmp(cur_item->name, items[correct_item]) == 0) {
                    printf("Item match\n");
                    item_match = true;
                    break;
                }
                cur_item = cur_item->next_item;
            }
            //if player has a room match, item match, and character match, they win the game!
            if (room_match && item_match && character_match) {
                printf("you win!\n");
                free_memory();
                exit(0);
            }

        }
        //user only has max of 10 clue uses, exit game if user reaches 10 and doesn't win
        if (clue_uses == 10) {
            printf("you used all your 10 clue guesses, game over :(\n");
            free_memory();
            exit(0);
        }
    }
}

