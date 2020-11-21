// Add header files and library here
#include <ncurses.h>
#include "library.h"
#include "menu.cpp"
#include "UI.h"

using namespace std;

int main(){
  bool end = false; // flag to turn game off
  int input;        // user input
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
      case KEY_BACKSPACE:
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
