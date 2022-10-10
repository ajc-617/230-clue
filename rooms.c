#include "rooms.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Room* room_array[NUM_ROOMS];

struct Room ** generateRooms() {
  srand(time(0));
  int i = rand() % NUM_ROOMS;
  /*rooms array that will be shuffled to randomly determine the locations of the rooms
  index for the rooms are as follows
  */

  int rooms[NUM_ROOMS] = {0,1,2,3,4,5,6,7,8};
  for (int i = NUM_ROOMS - 1; i > 0; i--) {
    int j = rand() % (i+1);
    int	temp = rooms[j];
    rooms[j] = rooms[i];
    rooms[i] = temp;
  }
  //array is now randomly ordered but we have to initialize array of room strucuts
  for (int i = 0; i < NUM_ROOMS; i++) {
    //say i is 0: when going into case statement first time, when doing room_array[i]->South = room_array[2] for example, this doesn't work as room_array[2] hasn't been malloced yet
    room_array[i] = (struct Room*) malloc(sizeof(struct Room));
  }
  //form connections between all of the rooms
  for (int i = 0; i < NUM_ROOMS; i++) {
    switch (i) {
      case STUDY:
        room_array[i]->South = room_array[3];
        room_array[i]->East = room_array[1];
        break;
      case LIBRARY:
        room_array[i]->West = room_array[0];
        room_array[i]->South = room_array[4];
        room_array[i]->East = room_array[2];
        break;
      case BILLARD_ROOM:
        room_array[i]->West = room_array[1];
        room_array[i]->South = room_array[5];
        break;
      case CONSERVATORY:
        room_array[i]->North = room_array[0];
        room_array[i]->South = room_array[6];
        room_array[i]->East = room_array[4];
        break;
      case HALL:
        room_array[i]->West = room_array[4];
        room_array[i]->North = room_array[1];
        room_array[i]->East = room_array[5];
        room_array[i]->South = room_array[7];
        break;
      case BALL_ROOM:
        room_array[i]->North = room_array[2];
        room_array[i]->West = room_array[4];
        room_array[i]->South = room_array[8];
        break;
      case LOUNGE:
        room_array[i]->North = room_array[3];
        room_array[i]->East = room_array[7];
        break;
      case DINING_ROOM:
        room_array[i]->West = room_array[6];
        room_array[i]->North = room_array[4];
        room_array[i]->East = room_array[8]; 
        break;
      case KITCHEN:
        room_array[i]->West = room_array[7];
        room_array[i]->North = room_array[5];
        break;
      default:
        printf("error, exiting program");
        exit(0);
    }
  }
  //now give all of the rooms names
  for (int i = 0; i < NUM_ROOMS; i++) {
    switch(rooms[i]) {
      case STUDY:
        room_array[i]->name = "study";
        break;
      case LIBRARY:
        room_array[i]->name = "library";
        break;
      case BILLARD_ROOM:
        room_array[i]->name = "billiard room";
        break;
      case CONSERVATORY:
        room_array[i]->name = "conservatory";
        break;
      case HALL:
        room_array[i]->name = "hall";
        break;
      case BALL_ROOM:
        room_array[i]->name = "ball room";
        break;
      case LOUNGE: 
        room_array[i]->name = "lounge";
        break;
      case DINING_ROOM:
        room_array[i]->name = "dining room";
        break;
      case KITCHEN:
        room_array[i]->name = "kitchen";
        break;
    }
  }
  return &room_array;
}