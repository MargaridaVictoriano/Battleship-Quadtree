#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include "global_var.h"
#include "coords.h"
#include "boat.h"
#include "board.h"
#include "utils.h"

/**
* Function name : showRules()
* Usage         : showRules();
* Definition    : This function displays the Battleship Rules.
*/

void showRules() {
  printf(".:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*._.:*~*:._.:*~*:._.:*~*._.:*~*:._.:*~*:._.:*~*._.:*~*:._.:*~*:._.:*~*:.*~*:._.:*~*:.\n");
  printf("                                                                RULES                                                                            \n");
  printf(".:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*._.:*~*:._.:*~*:._.:*~*._.:*~*:._.:*~*:._.:*~*._.:*~*:._.:*~*:._.:*~*:.*~*:._.:*~*:.\n");
  printf("\n");
  printf("1. This is a two player game.\n");
  printf("2. You will be prompted to insert the maximum board size.\n");
  printf("  Please keep in mind that both players must play with boards of equal size\n");
  printf("  so you will only be prompted once to input the size which cannot be changed throughout the game.\n");
  printf("3. You will be prompted to insert how many boats you want from each type.\n");
  printf("  Please keep in mind that both players must play with the same number of boats\n");
  printf("  so you will only be prompted once to input the number of boats which cannot be changed throughout the game.\n");
  printf("  You must choose atleast one boat of each type.\n");
  printf("4. Players will be prompted to choose how to place the boats on the map: randomly or manually.\n");
  printf("  4.1. Random Mode:\n");
  printf("       .:Players will see the map with the boats randomly placed for a few seconds.\n");
  printf("  4.2. Manual Mode:\n");
  printf("       .:Players will enter the desired boat ID and then they will be prompted to choose the: \n");
  printf("       .:X coordinates\n");
  printf("       .:Y coordinates\n");
  printf("       .:Rotation : 0,90,270,360 degrees\n");
  printf("until all boats are placed.\n");
  printf("5. When the game begins the players take turns attacking each other and they can view their own map and their attack map whenever they want.\n");
  printf("6. The first player to guess the location of all ships wins!\n\n");
  printf(".:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*._.:*~*:._.:*~*:._.:*~*._.:*~*:._.:*~*:._.:*~*._.:*~*:._.:*~*:._.:*~*:.*~*:._.:*~*:.\n");
  printf(".:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*._.:*~*:._.:*~*:._.:*~*._.:*~*:._.:*~*:._.:*~*._.:*~*:._.:*~*:._.:*~*:.*~*:._.:*~*:.\n");
  printf("\n");

  printf("Press any key to continue.\n");

  flushInput();

  system("clear");
}

/**
* Function name : Battleship()
* Usage         : Battleship();
* Definition    : This function displays a welcome screen with the main menu.
*/

void Battleship() {
  printf("@@@@@   @@@@  @@@@@@ @@@@@@ @@     @@@@@@  @@@@@ @@  @@ @@ @@@@  \n");
  printf("@@  @@ @@  @@   @@     @@   @@     @@     @@     @@  @@ @@ @@  @@\n");
  printf("@@@@@  @@  @@   @@     @@   @@     @@@@    @@@@  @@@@@@ @@ @@@@  \n");
  printf("@@  @@ @@@@@@   @@     @@   @@     @@         @@ @@  @@ @@ @@    \n");
  printf("@@@@@  @@  @@   @@     @@   @@@@@@ @@@@@@ @@@@@  @@  @@ @@ @@    \n");
  printf("\n");
  int mode;
  while (1) {
    printf("\n");
    printf("Select one of the following options.\n");
    printf("1 :: Start\n");
    printf("2 :: Rules\n");
    printf("3 :: Quit\n");
    scanf("%d",&mode);
    flushInput();
    if (mode >= 1 && mode <= 3) break;
    printf("Invalid mode. Please try again.\n");
  }
  switch(mode) {
    case 2: showRules();
    return;
    case 3:
    exit(0);
    case 1:
    default: return;
  }

}

/**
* Function name : pickMatrixSize()
* Usage         : pickMatrixSize();
* Definition    : This function receives the matrix size from the stdin and checks if the value is within range.
*/

void pickMatrixSize() {
  printf("Please insert the matrix size.\n");
  printf("Both users will use the same matrix size.\n");
  printf("The matrix minimum size is %d and the matrix maximum size is %d.\n", MIN_MATRIX, MAX_MATRIX);

  while (1) {
    scanf("%d", &n_matrix);
    flushInput();
    if (n_matrix >= MIN_MATRIX && n_matrix <= MAX_MATRIX) break;
    printf("Invalid input. Please try again.\n");
  }
}

/**
* Function name : pickNumberBoats()
* Usage         : pickNumberBoats();
* Definition    : This function receives the number of boats of each type from the stdin and checks if the values are within range.
*/

void pickNumberBoats() {
  int max_boats = (n_matrix*n_matrix)/(BITMAP_SIZE*BITMAP_SIZE);

  printf("Please insert how many boats you want from each type.\n");
  printf("The maximum number of boats is: %d.\n", max_boats);
  printf("Boats Available and ID: \n");
  for(int i=0; i<n_boats; i++){
    char id = listBoat[i];
    printf("%c ",id);
  }
  printf("\n");

  while(1) {
    bool minValue = true;
    sum_boats = 0;
    for(int i=0; i<n_boats; i++) {
      scanf("%d",&boat_number[i]);
      if(boat_number[i] < 1) {
        minValue = false;
      }
      sum_boats += boat_number[i];
    }
    flushInput();

    if(sum_boats <= max_boats && minValue) break;
    printf("Invalid input. Please try again.\n");
  }
}

/**
* Function name : pickBoatPosition()
* Usage         : pickBoatPosition(Board*);
* Definition    : This function receives the coordinates and rotation to place each boat which is identified by its ID.
*/

void pickBoatPosition(Board* map) {
  int copy[n_boats];
  for(int i=0; i<n_boats; i++){
    copy[i] = boat_number[i];
  }
  
  for (int i = 0; i < sum_boats;) {
    char boatId;
    int x,y,rot;

    printf("Available Boats and corresponding ID: \n");
    for(int j=0; j<n_boats; j++){
      if(copy[j] > 0){
        char id = listBoat[j];
        printf("'%c' :: %s\n",id,boatName(id));
      }
    }
    printf("\n");

    while (1) {
      printf("Please enter the desired Boat ID: \n");
      boatId = getchar();
      flushInput();
      if(indexBoat(boatId) != -1 && copy[(unsigned char)indexBoat(boatId)] > 0) break;
      printf("Invalid input. Please try again.\n");
    }

    printf("Please enter the desired coordinates for the boat: \n");
    printf("Coordinate X:\n");
    scanf("%d", &x);

    printf("Coordinate Y:\n");
    scanf("%d", &y);

    printf("Please Insert the desired Rotation:\n");
    printf("Only 0, 90, 180, 270 and 360 degrees is accepted\n");
    scanf("%d", &rot);

    flushInput();

    Coords *boat_pos = (Coords *)buildCoords(x,y,rot);
    if (isAvailablePosition(map, boatId, boat_pos)) {
      insertBoat(map, boatId, boat_pos);
      printf(" %d antes \n",copy[(unsigned char)indexBoat(boatId)]);
      copy[(unsigned char)indexBoat(boatId)]--;
      printf(" %d depois \n",copy[(unsigned char)indexBoat(boatId)]);
      i++;
      printDefenseBoard(map);
      printf("\n");
    }
    else {
      destroyCoords(boat_pos);
      printf("\nInvalid input. Please try again.\n\n");
    }
  }
}

/**
* Function name : placeBoat()
* Usage         : placeBoat(Board*);
* Definition    : This function allows user to choose how they want to place the boats: manually or randomly.
*/

void placeBoat(Board* map) {
  char mode;

  printf("Select the prefered mode to insert the boats: \n");
  printf("'r' :: random\n");
  printf("'m' :: manual\n");

  while (1) {
    printf("Select the mode:\n");
    mode = getchar();
    flushInput();
    if (mode == 'r' || mode == 'm') break;
    printf("Invalid mode. Please try again.\n");
  }

  if (mode == 'r') randomlyPlaceBoatonBoard(map);
  else pickBoatPosition(map);

  printDefenseBoard(map);
}

/**
* Function name : attack()
* Usage         : attack(Board*,Board*);
* Definition    : This function receives the attack coordinates anc checks whether there is a hit, a miss or if a ship is destroyed.
*/

bool attack(Board* att, Board* def) {
  int x, y;

  scanf("%d", &x);
  scanf("%d", &y);
  flushInput();

  if(x >= 0 && y >= 0 && x < n_matrix && y < n_matrix && att -> map[x*n_matrix + y].shot == 0) {
    int i = x * n_matrix + y;
    if (def -> map[i].state == 1) {
      att -> map[i].shot = 2;
      def -> map[i].state = 2;
      def -> map[i].ship -> hp--;
      setShip(def -> map[i].ship, 2, x, y);
      if(def -> map[i].ship -> hp == 0) {
        printf("The ship %s was just destroyed !\n\n", boatName(def -> map[i].ship -> id));
        def -> remainingBoats--;
      }
      else printf("HIT!\n");
    }
    else {
      att -> map[i].shot = 1;
      def -> map[i].state = 3;
      printf("MISS!\n");
    }

    return true;
  }
  else printf("Invalid input. Please try again.\n");
  return false;
}

/**
* Function name : gameInterface()
* Usage         : gameInterface(Board*);
* Definition    : This function allows the user to choose whether they want to see their defense map, their attack map or to attack.
*/

bool gameInterface(Board* p) {
  int mode;
  while (1) {
    printf("\n");
    printf("Select one of the following options.\n");
    printf("1 :: Defense Map\n");
    printf("2 :: Attack Map\n");
    printf("3 :: Attack !!!\n");
    scanf("%d",&mode);
    flushInput();
    if (mode >= 1 && mode <= 3) break;
    printf("Invalid mode. Please try again.\n");
  }
  switch(mode) {
    case 1: printDefenseBoard(p);
    return false;
    case 2: printAttackBoard(p);
    return false;
    case 3:
    return true;
  }
  return false;
}

/**
* Function name : game()
* Usage         : game(Board*,Board*);
* Definition    : This function attacks with the received coordinates until one of the players win.
*/

void game(Board* p1, Board* p2) {
  p1 -> remainingBoats = sum_boats;
  p2 -> remainingBoats = sum_boats;
  while(p1 -> remainingBoats > 0 && p2 -> remainingBoats > 0) {

    //Player1 attack
    printf(":*~*:._.::*~*:._.::*~*:._.:\n");
    printf(":.        Player1        .:\n");
    printf(":*~*:._.::*~*:._.::*~*:._.:\n");
    while(!gameInterface(p1));
    printf("Player1 please select the attack coordinates.\n");
    while(!attack(p1,p2));

    sleep(3);
    system("clear");
    if(p2 -> remainingBoats == 0) break;

    //Player2 attack
    printf(":*~*:._.::*~*:._.::*~*:._.:\n");
    printf(":.        Player2        .:\n");
    printf(":*~*:._.::*~*:._.::*~*:._.:\n");
    while(!gameInterface(p2));
    printf("Player2 please select the attack coordinates.\n");
    while(!attack(p2,p1));

    sleep(3);
    system("clear");
  }

  if (p1 -> remainingBoats == 0) printf("Player2 wins !\n");
  else printf("Player1 wins !\n");

}

int main() {
  srand(time(NULL)); // randomize seed

  system("clear");
  Battleship();

  pickMatrixSize();
  system("clear");

  pickNumberBoats();
  system("clear");

  //Board player1
  printf(":*~*:._.::*~*:._.::*~*:._.:\n");
  printf(":.        Player1        .:\n");
  printf(":*~*:._.::*~*:._.::*~*:._.:\n");
  printf("\n");
  Board* p1 = (Board *) buildBoard();
  placeBoat(p1);
  sleep(3);
  system("clear");

  //Board player2
  printf(":*~*:._.::*~*:._.::*~*:._.:\n");
  printf(":.        Player2        .:\n");
  printf(":*~*:._.::*~*:._.::*~*:._.:\n");
  printf("\n");

  Board* p2 = (Board *) buildBoard();
  placeBoat(p2);
  sleep(3);
  system("clear");

  game(p1,p2);

  destroyBoard(p1);
  destroyBoard(p2);
}
