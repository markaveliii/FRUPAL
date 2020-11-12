// Add header files and library here
#include <ncurses.h>

using namespace std;

int main(){
  bool end = false; // flag to turn game off
  int input;        // user input

  initscr();

  keypad(stdscr, true);
  noecho();

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
