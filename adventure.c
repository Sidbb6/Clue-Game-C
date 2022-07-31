#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "rooms.h"

//Global Variable Declaration
#define NUM_ROOMS 9
struct Room* boardHead;
int curRoomNum;
int murderRoomNum; 
struct Item* inventory; 
int numTries;

//Method Declaration
struct Room* genBoard(void);
int* randArrGen(int n); 
void pBegInstruct(void);
void pCmds(void);
void game(void);
void endGame(void);

int main(void) {
  boardHead = genBoard();  
  pBegInstruct();
  game();
  endGame();

  return 0;
}

// Generating and filling the game board
struct Room* genBoard() {
  // malloc = memory allocation for the 9 rooms with the pointer to the first address. 
  struct Room* curRoom = (struct Room*)malloc(sizeof(struct Room) * NUM_ROOMS);
  struct Item* curItem = (struct Item*)malloc(sizeof(struct Item) * NUM_ROOMS); 
 
  char* roomNames[] = { "kitchen", "study", "cellar", 
                        "library", "lounge", "garage", 
                        "dungeon", "greenhouse", "bedroom" }; 

  char* avatarNames[] = { "Joe", "Emily", "Marius",
			  "Sas", "Sam", "Shaun",
                          "Prommy", "Sid", "F30_335i" };

  // Using a unique random number generator with indices from 0 to 8 to assign assets randomly to rooms
  int* ranArr = randArrGen(NUM_ROOMS);
  
  for(int i = 0; i < NUM_ROOMS; i++) {
    switch (i) {
      // Top Row
      case 0:
        curRoom[i].north = NULL;
        curRoom[i].east = &curRoom[i+1];
        curRoom[i].south = &curRoom[i+3];
        curRoom[i].west = NULL;
        curItem[i].name = "scalpel"; 

        break;
      case 1: 
        curRoom[i].north = NULL;
        curRoom[i].east = &curRoom[i+1];
        curRoom[i].south = &curRoom[i+3];
        curRoom[i].west = &curRoom[i-1];
        curItem[i].name = "mask";
        
        break;
      case 2:
        curRoom[i].north = NULL;
        curRoom[i].east = NULL;
        curRoom[i].south = &curRoom[i+3];
        curRoom[i].west = &curRoom[i-1];
        curItem[i].name = "hammer";

        break;
      // Middle Row
      case 3:
        curRoom[i].north = &curRoom[i-3];
        curRoom[i].east = &curRoom[i+1];
        curRoom[i].south = &curRoom[i+3];
        curRoom[i].west = NULL;
        curItem[i].name = "bag";

        break;
      case 4:
        curRoom[i].north = &curRoom[i-3];
        curRoom[i].east = &curRoom[i+1];
        curRoom[i].south = &curRoom[i+3];
        curRoom[i].west = &curRoom[i-1];
        curItem[i].name = "wand";

        break;
      case 5:
        curRoom[i].north = &curRoom[i-3];
        curRoom[i].east = NULL;
        curRoom[i].south = &curRoom[i+3];
        curRoom[i].west = &curRoom[i-1];
        curItem[i].name = "wrench";

        break;
      //Bottom Row
      case 6:
        curRoom[i].north = &curRoom[i-3];
        curRoom[i].east = &curRoom[i+1];
        curRoom[i].south = NULL;
        curRoom[i].west = NULL;
        curItem[i].name = "wire";

        break;
      case 7:
        curRoom[i].north = &curRoom[i-3];
        curRoom[i].east = &curRoom[i+1];
        curRoom[i].south = NULL;
        curRoom[i].west = &curRoom[i-1];
        curItem[i].name = "cat";

        break;
      case 8:
        curRoom[i].north = &curRoom[i-3];
        curRoom[i].east = NULL;
        curRoom[i].south = NULL;
        curRoom[i].west = &curRoom[i-1];
        curItem[i].name = "bucket";

        break;
    }
    
    curRoom[i].name = roomNames[ranArr[i]];
    curRoom[i].itemList = &curItem[ranArr[i]];
    curRoom[i].avatar = avatarNames[ranArr[i]];
    curRoom[i].murder = 0;
  }

  murderRoomNum = ranArr[1];
  curRoom[murderRoomNum].murder = 1; 
  curRoomNum = ranArr[0];
  
  printf("%d", murderRoomNum);
  printf("%d", curRoomNum);

  numTries = 0;

  return curRoom;
}

//Random number array generator, returns pointer to the array in memory, could definetly have better time and space complexity
int* randArrGen(int n) {
  srand(time(NULL));

  int* curNum = (int*)malloc(sizeof(int) * n);

  int i,j,r;
  for(i = 0; i < n; i++) {
    r = rand() % n;

    for(j = 0; j < i; j++) {
      while(r == curNum[j]) {
        r = rand() % n;
      }
    }

    curNum[i] = r;
  }

  return curNum;
}

//Prints beginning text instructions
void pBegInstruct() {
  printf("\n\n\n\n");
  printf("---------------------------------------------------------------- \n");
  printf("Your name is Detective Yeager and you are tasked with answering the questions of: \n");
  printf("Who did it, with what, and where. \n");
  printf("You are currently in the %s with no items in your inventory. \n", boardHead[curRoomNum].name); 
  printf("What is your next move? \n");

  pCmds();
}

//Prints list of commands
void pCmds() {
  printf("\n** \n");
  printf("List of Commands: (Note: Uppercase Only) \n");
  printf("-------------------------------- \n");
  printf("  Informational Commands \n");
  printf("\tHELP:      Type help for help. \n");
  printf("\tLIST:      List of items, rooms, and characters. \n");
  printf("\tLOOK:      See current room, surrounding rooms, characters, and items. \n");
  printf("\tINVENTORY: Curent inventory. \n");
  printf("-------------------------------- \n");
  printf("  Action Commands \n");
  printf("\tGO <DIRECTION>:   Move to next room either NORTH, SOUTH, EAST, or WEST. \n");
  printf("\tTAKE <ITEM NAME>: Pick up item and store in inventory. \n");
  printf("\tDROP <ITEM NAME>: Drop an item and remove from inventory. \n");
  printf("**\n\n");
}

//Prints all the assets in the game
void pAssets() {
  printf("\n-------------------------------- \n");
  printf("Room Names\n");
  for(int i = 0; i < NUM_ROOMS; i++) {
    char str[11]; 
    strcpy(str, boardHead[i].name);
    (i != NUM_ROOMS - 1) ? printf("%s, ", str) : printf("%s\n", str);
  } 
  
  printf("\nCharacter Names\n");
  for(int i = 0; i < NUM_ROOMS; i++) {
    char str[11];
    strcpy(str, boardHead[i].avatar);
    (i != NUM_ROOMS - 1) ? printf("%s, ", str) : printf("%s\n", str);
  }

  printf("\nItem Names\n");
  for(int i = 0; i < NUM_ROOMS; i++) {
    char str[11];
    strcpy(str, boardHead[i].itemList->name);
    (i != NUM_ROOMS - 1) ? printf("%s, ", str) : printf("%s\n\n", str);
  }
}

//Prints whats in the current room
void pCurRoomAssets() {
  struct Room occuRoom = boardHead[curRoomNum];

  printf("\n-------------------------------- \n");
  printf("*Looking Around*\n");
  printf("You are in the %s.\n\n", occuRoom.name);

  ((curRoomNum - 3) > 0) ? printf("The %s is to the North.\n", boardHead[curRoomNum-3].name) : printf("There are no rooms to the North.\n");
  ((curRoomNum + 1) < NUM_ROOMS) ? printf("The %s is to the East.\n", boardHead[curRoomNum+1].name) : printf("There are no rooms to the East.\n");
  ((curRoomNum + 3) < NUM_ROOMS) ? printf("The %s is to the South.\n", boardHead[curRoomNum+3].name) : printf("There are no rooms to the South.\n");
  ((curRoomNum - 1) > 0) ? printf("The %s is to the West.\n\n", boardHead[curRoomNum-1].name) : printf("There are no rooms to the West.\n\n");

/* Getting a segmentation error presumably because when a direction is null, the -> call causes it to throw the error
  ((curRoomNum - 3) > 0) ? printf("The %s is to the North.\n", boardHead[curRoomNum].north->name) : printf("There are no rooms to the North.\n");
  ((curRoomNum + 1) < NUM_ROOMS) ? printf("The %s is to the East.\n", boardHead[curRoomNum].east->name) : printf("There are no rooms to the East.\n");
  ((curRoomNum + 3) < NUM_ROOMS) ? printf("The %s is to the South.\n", boardHead[curRoomNum].south->name) : printf("There are no rooms to the South.\n");
  ((curRoomNum - 1) > 0) ? printf("The %s is to the West.\n\n", boardHead[curRoomNum].west->name) : printf("There are no rooms to the West.\n\n");
*/
  
  //Prints items and does linked list traversal to achieve this
  struct Item * foundItem = occuRoom.itemList;
  if (foundItem == NULL) {
    printf("There are no items in this room.\n");
  } else {  
    while(foundItem != NULL) {
      printf("There is a %s.\n", foundItem->name);
      foundItem = foundItem->next;
    }
  }

  printf("\n%s is in the room with you.\n\n", occuRoom.avatar);

  if (occuRoom.murder == 1) { 
    printf("You observe the room has blood on the walls...\n");
    printf("An item is broken.\n");
    printf("%s has a nervous look on their face.\n", occuRoom.avatar);
  } else {
    printf("You observe the room has no signs of a murder.\n");
    printf("An item is unused.\n");
    printf("%s has a neutral look on their face.\n", occuRoom.avatar);
  }
}

//Traverses through the game board
void traverse(char dir[]) {
  printf("\n");
  if(strcmp(dir, "NORTH") == 0) {
    if(curRoomNum - 3 < 0) {
      printf("You cannot go North."); 
    } else {
      curRoomNum -= 3;
      printf("You traveled North. Use LOOK to see your new surroundings.");
    }
  } else if (strcmp(dir, "EAST") == 0) {
    if (curRoomNum + 1 > NUM_ROOMS) { 
      printf("You cannot go East."); 
    } else { 
      curRoomNum += 1;
      printf("You traveled East. Use LOOK to see your new surroundings.");
    }
  } else if (strcmp(dir, "SOUTH") == 0) {
    if (curRoomNum + 3 > NUM_ROOMS) { 
      printf("You cannot go South."); 
    } else { 
      curRoomNum += 3;
      printf("You traveled South. Use LOOK to see your new surroundings.");
    }
  } else if (strcmp(dir, "WEST") == 0) {
    if (curRoomNum - 1 < 0) {
      printf("You cannot go West."); 
    } else {
      curRoomNum -= 1;
      printf("You traveled West. Use LOOK to see your new surroundings.");
    }
  } else {
    printf("Invalid direction.");
  }
  printf("\n\n");
}

//Prints and traverses through player's inventory
void pInventory() {
  struct Item * curItem = inventory;
 
  if (curItem == NULL) {
    printf("\nThere are no items in your inventory.\n\n");
  } else {
    printf("\n"); 
    while(curItem != NULL) {
      printf("\n%s", curItem->name);
      curItem = curItem->next; 
    }
  }
}

//Picks uo items (unfinished, need to pick up items if already posessing at least one)
void take(char obj[]) {
  struct Room occuRoom = boardHead[curRoomNum];
  struct Item * foundItem = occuRoom.itemList;

  if(foundItem != NULL) {
    if(inventory != NULL) {
       

    } else {
      if(strcmp(foundItem->name, obj) == 0) {
        inventory = foundItem; 
      } else {
        printf("\nItem names do not match.\n\n"); 
      }
    }  
  } else {
    printf("\nThere are no items to take in this room.\n\n");
  }  
}

//Drops items but not actually
void drop(char obj[]) {
  if(inventory != NULL) {

  } else {
    printf("\nYou have no items to drop.\n\n");
  }
}

//Clue command
int clue(char avatar[]) {
  struct Room occuRoom = boardHead[curRoomNum];

  if(curRoomNum == murderRoomNum && strcmp(avatar, occuRoom.avatar) == 0) {
    printf("\nRoom Match\n");
    printf("\nItem Match\n");
    printf("\nCharacter Match\n");
      
    printf("\n\n\n-------------------------------- \n");
    printf("YOU WIN!\n\n");
     
    return 1;  
  } else {
    printf("Incorrect guess.\n"); 
    numTries++;
  }

  if (numTries == 10) {
    printf("\n\n\n-------------------------------- \n");
    printf("YOU LOSE!\n\n");

    return 1;
  }

  return 0;
}

//Game driver function
void game() {
  int run = 1;

  while(run == 1) {
    char cmd[15];
    printf("Command: ");
    scanf("%[^\n]%*c", cmd);

    if(strcmp(cmd, "HELP") == 0) { pCmds(); }
    else if(strcmp(cmd, "LIST") == 0) { pAssets(); } 
    else if(strcmp(cmd, "LOOK") == 0) { pCurRoomAssets(); } 
    else if(strcmp(cmd, "INVENTORY") == 0) { pInventory(); } 
    else if(strstr(cmd, "GO ") != NULL) {
      char dir[6];
      memcpy(dir, &cmd[3], 5);
      dir[5] = '\0';

      traverse(dir);
    } else if(strstr(cmd, "TAKE ") != NULL) {
      char obj[8];
      memcpy(obj, &cmd[5], 7);
      obj[7] = '\0';

      take(obj);
    } else if(strstr(cmd, "DROP ") != NULL) {
      char obj[8];
      memcpy(obj, &cmd[5], 7);
      obj[7] = '\0';

      drop(obj);
    } else if(strstr(cmd, "CLUE ") != NULL) {
      char avatar[9];
      memcpy(avatar, &cmd[5], 8);
      avatar[8] = '\0';

      if(clue(avatar) == 1) { run = 0; } 
    } else {
      printf("Invalid command.\n"); 
    }
  }
}

//This finished method deallocates memory and closes the game
void endGame() {

}
