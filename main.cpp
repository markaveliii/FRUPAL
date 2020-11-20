// Add header files and library here
#include <ncurses.h>
#include "library.h"
#include "menu.cpp"

using namespace std;

int main(){
  bool end = false; // flag to turn game off
  int input;        // user input
  food f;
  f.cost = 10;
  f.fill = 5;
  
  cell c;
  c.foodUnit = &f;
  c.symbol = 'T';
  hero p1;
  p1.cash = 100;
  p1.energy = 100;

  initscr();

  keypad(stdscr, true);
  noecho();

  WINDOW *menu = create_game_menu();
  display_EW(menu, p1);
  display_cell(menu, c);
  wrefresh(menu);
  // start game
  while(!end){
    switch((input = getch())){
      // end game
      case KEY_END:
        end = true;
        break;

      default:
        break;
    }
    refresh();
  }

  // close window
  endwin();

  return 0;
}
