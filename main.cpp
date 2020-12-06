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
  int win = 0;      // win check

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
  visitArea(kingdom, player);
  mapgen(kingdom, player);
  WINDOW *GW = create_game_menu();
  display_EW(GW, player);
  display_movement(GW);
  player.backpack.display(GW);
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

      case 'W':
      case 'w':
      case 'A':
      case 'a':
      case 'S':
      case 's':
      case 'D':
      case 'd':
      //case 'r':
      //case 'R':
        movement(kingdom, player, input);
        visitArea(kingdom, player);
        mapgen(kingdom, player);

        // clue found
        if(kingdom[player.y_pos][player.x_pos].symbol == '?'){
          display_EW(GW, player);
          mapgen(kingdom, player);
          wrefresh(GW);
          --player.clue_counter;
          kingdom[player.y_pos][player.x_pos].symbol = '/';
          wmove(GW, LINES/5 + 4, 2);
          wclrtoeol(GW);
          mvwprintw(GW, LINES/5 + 4, 2, kingdom[player.y_pos][player.x_pos].clue);
          wmove(GW, LINES/5 + 5, 2);
          wclrtoeol(GW);
          mvwprintw(GW, LINES/5 + 5, 2, "Press any key to continue");
          wrefresh(GW);
          getch();
          wmove(GW, LINES/5 + 4, 2);
          wclrtoeol(GW);
          wmove(GW, LINES/5 + 5, 2);
          wclrtoeol(GW);
          wrefresh(GW);
        }
        
        //handles if player lands on an obstacle
        if(kingdom[player.y_pos][player.x_pos].obsType) {

          display_obstacle(GW, kingdom[player.y_pos][player.x_pos]);
          display_EW(GW, player);

          if(tool_prompt(GW)) {
            int num = 0;
            mvwprintw(GW, LINES/5 + 3, 2, "choose weapon (numpad) or (q)uit");
            wrefresh(GW);

            while(num != ('q'-49)) {
              num = getch();
              num -= 49;

              if(player.backpack.retrieve_tool(num)) {
                tool * equipped = player.backpack.retrieve_tool(num);
                obstacle * obs = kingdom[player.y_pos][player.x_pos].obsType;

                if(strcmp(equipped->name, obs->tool) == 0) {
                  player.use_tool(equipped, obs);
                  kingdom[player.y_pos][player.x_pos].obsType = NULL;
                  kingdom[player.y_pos][player.x_pos].symbol = '/';
                  player.backpack.remove(num);
                  num = 'q'-49;
                }
                else {
                clearblock(GW, LINES/5+4, 1);
                mvwprintw(GW, LINES/5 + 4, 2, "You did not pick the right weapon try again");
                }
              }
              else {
                clearblock(GW, LINES/5+4, 1);
                mvwprintw(GW, LINES/5 + 4, 2, "invalid");
              }
              wrefresh(GW);
            }
          }
          clearblock(GW,LINES/5,6);
        }

        //handles if player encounters a ship
        if(kingdom[player.y_pos][player.x_pos].symbol == 'S') {
        player.has_ship = false;
        mvwprintw(GW, LINES/5, 2, "Hey there dandy. Would you like");
        mvwprintw(GW, LINES/5 + 1, 2, "to buy my ship for 50 whiffles? y/n");
        display_EW(GW, player);
        wrefresh(GW);
          if(prompt(GW)) {
            if(player.purchase_ship()) {
              purchase_success();
              player.has_ship = true;
              kingdom[player.y_pos][player.x_pos].symbol = '/';
              mapgen(kingdom,player);
            }
            else  purchase_failed();
          }
          clearblock(GW, LINES/5, 6);
        }

        clearblock(GW,LINES/2 + 1, 10);
        player.backpack.display(GW); 
        wrefresh(GW);
        kingdom[curs.y_pos][curs.x_pos].curs = false;
        curs.x_pos = player.x_pos;
        curs.y_pos = player.y_pos;
        break;

      case 'p':
      case 'P': 
       if(kingdom[player.y_pos][player.x_pos].toolDevice) {
          if(player.purchase_tool(kingdom[player.y_pos][player.x_pos].toolDevice)) {
          purchase_success();
          kingdom[player.y_pos][player.x_pos].toolDevice = NULL;
          kingdom[player.y_pos][player.x_pos].symbol = '/';
          }
          else purchase_failed();
        }
        else if(kingdom[player.y_pos][player.x_pos].foodUnit) {
          if(player.purchase_food(kingdom[player.y_pos][player.x_pos].foodUnit)) {
            purchase_success();
            kingdom[player.y_pos][player.x_pos].foodUnit = NULL;
            kingdom[player.y_pos][player.x_pos].symbol = '/';
          }
          else purchase_failed();
        }
        //Handle treasure
        else if(kingdom[player.y_pos][player.x_pos].symbol == '$') {
          player.whiffle += kingdom[player.y_pos][player.x_pos].treasureChest->whiffle;
          kingdom[player.y_pos][player.x_pos].symbol = '/';
        }
        player.backpack.display(GW);
        wrefresh(GW);
        break;


      case 258 ... 261:
        move_cursor(stdscr, GW, kingdom, curs, input);
        break;

      default:
        break;
    }

    mapgen(kingdom,player);
    display_EW(GW, player);
    display_cell(GW, kingdom[curs.y_pos][curs.x_pos]);
    wrefresh(GW);
    if(kingdom[player.y_pos][player.x_pos].symbol == 'R'){
      end = true;
      win = 1;
    }
    if(player.energy <= 0){
      end = true;
    }
  }

  // close window
  endwin();

  if(player.energy <= 0){
    cout << "\nYou have lost the game.\n";
  }
  if(win == 1){
    cout << "\nYou have won the game.\n";
  }

  return 0;
}
