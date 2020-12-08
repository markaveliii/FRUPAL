#include "mode.h"

int mode_select(){
  mvprintw(((LINES / 2) - 4), COLS / 2 - 30, "Use 'W' and 'S' to move cursor, press 'P' to select mode");
  mvprintw(((LINES / 2) - 3), COLS / 2 - 14, "Press End key to exit game");
  mvprintw(((LINES / 2) - 1), COLS / 2 - 7, "----Modes----");
  mvprintw(LINES / 2, (COLS / 2) - 4, "Default");
  mvprintw((LINES / 2) + 1, (COLS / 2) - 4, "Random");

  int input;
  bool end = false;
  int mode;
  int y = LINES / 2;
  move(y, (COLS / 2) - 5);
  noecho();
  keypad(stdscr, true);

  while(!end){
    switch((input = getch())){
      case 'w':
        if(y > (LINES / 2)){
          --y;
          move(y, (COLS / 2) - 5);
        }
        break;
      case 'W':
        if(y > (LINES / 2)){
          --y;
          move(y, (COLS / 2) - 5);
        }
        break;
      case 's':
        if(y < ((LINES / 2) + 1)){
          ++y;
          move(y, (COLS / 2) - 5);
        }
        break;
      case 'S':
        if(y < ((LINES / 2) + 1)){
          ++y;
          move(y, (COLS / 2) - 5);
        }
        break;
      case 'p':
        if(y == (LINES / 2))
          mode = 1;
        else
          mode = 2;
        end = true;
        break;
      case 'P':
        if(y == (LINES / 2))
          mode = 1;
        else
          mode = 2;
        end = true;
        break;
      case KEY_END:
        mode = 3;
        end = true;
        break;
    }
  }

  return mode;
}
