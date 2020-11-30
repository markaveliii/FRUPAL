// Add header files and library here
#include <ncurses.h>
#include "map.h"
#include "maploader.h"
#include "menu.h"
#include "UI.h"

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

  curs.x_pos = player.x_pos;
  curs.y_pos = player.y_pos;
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
    wrefresh(GW);
  keypad(stdscr, true);
  noecho();

  // start game
  while(!end){
    switch((input = getch())){
      // end game
      case KEY_END:
        end = true;
        break;
      case 'p':
        movement(kingdom, player);
        mapgen(kingdom,player);
        break;

      case 'P':
        movement(kingdom, player);
        mapgen(kingdom,player);
        break;

      case 'c':
        move_cursor(stdscr, GW, kingdom, curs);
        break;

      case 'C':
        move_cursor(stdscr, GW, kingdom, curs);
        break;

        

      default:
        
        break;
    }
    display_EW(GW, player);
    wrefresh(GW);
  }

  // close window
  endwin();

  return 0;
}
