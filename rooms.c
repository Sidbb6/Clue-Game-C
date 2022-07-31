#include "items.h"

struct Room {
  char* name;
  char* avatar;
  struct Item * itemList;   
  // If the room is occupied then val = 1 else 0 
  int murder; 

  struct Room * north;
  struct Room * south;
  struct Room * east;
  struct Room * west;
};
