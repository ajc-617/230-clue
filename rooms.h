#ifndef ROOMS_H
#define ROOMS_H

#include <stdio.h>
#include <stdbool.h>

#define STUDY 0
#define LIBRARY 1
#define BILLARD_ROOM 2
#define CONSERVATORY 3
#define HALL 4
#define BALL_ROOM 5
#define LOUNGE 6
#define DINING_ROOM 7
#define KITCHEN 8
#define NUM_ROOMS 9
#define NUM_CHARACTERS 5

struct Room {
    char* name;
    struct Room* North;
    struct Room* South;
    struct Room* East;
    struct Room* West;
    struct Item* itemList;
    bool characters[NUM_CHARACTERS]; 
};

struct Room** generateRooms();

#endif
