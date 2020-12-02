// Add header files and library here
#include <ncurses.h>
#include "map.h"
#include "maploader.h"
#include "menu.h"
#include "UI.h"
#include "visit.h"

using namespace std;
#define EMPTY      0
#define PLAYER     1
#define MEADOW     2
#define SWAMP      3
#define WATER      4
#define WALL       5
#define GOAL       6

int main(){
  bool end = false; // flag to turn game off
  int input;        // user input

  cell kingdom[128][128];
  obstacle obsList[100];
  food foodList[100];
  tool toolList[100];
  treasure chestList[100];
  hero player;
  cursor curs;
  initscr();

  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
}


  if(mapExport("map1.txt", kingdom, obsList, foodList, toolList, chestList, player) != 0){
    cout << "\nFailed to load map\n";
    exit(1);
  }

/*
  cout << COLS;
  cout << "\n";
  cout << LINES;
  cout << "\n";
*/
  
  start_color();
  init_pair(EMPTY, COLOR_GREEN, COLOR_GREEN);
  init_pair(PLAYER, COLOR_BLACK, COLOR_RED);
  init_pair(MEADOW, COLOR_GREEN, COLOR_GREEN);
  init_pair(SWAMP, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(WATER, COLOR_BLACK, COLOR_BLUE);
  init_pair(WALL, COLOR_BLACK, COLOR_WHITE);
  init_pair(GOAL, COLOR_BLACK, COLOR_CYAN);
  //WINDOW * GAME_MENU = create_game_menu();
  mapgen(kingdom, player);
  WINDOW *GW = create_game_menu();
  display_EW(GW, player);
  display_movement(GW);
  player.backpack.display(GW);
  wrefresh(GW);

  keypad(stdscr, true);
  noecho();
  curs.x_pos = player.x_pos;
  curs.y_pos = player.y_pos;

  // start game
  while(!end){
    switch((input = getch())){
      // end game
      case KEY_END:
        end = true;
        break;

      case 49 ... 53:
        movement(kingdom, player, input);
        visitArea(kingdom, player);
        mapgen(kingdom,player);
    
        player.backpack.display(GW); 
        wrefresh(GW);
        break;

      case 258 ... 261:
        move_cursor(stdscr, GW, kingdom, curs, input);
        break;

      default:
        break;
    }
    display_EW(GW, player);
    display_cell(GW, kingdom[curs.y_pos][curs.x_pos]);
    wrefresh(GW);
    display_cursor(stdscr, curs, kingdom[curs.y_pos][curs.x_pos]);
  }

  // close window
  endwin();

  return 0;
}
