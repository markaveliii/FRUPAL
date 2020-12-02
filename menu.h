//takes one quarter (most to the right) and creates a window that handles the game menu
WINDOW * create_game_menu() {
  WINDOW * GAME_MENU = newwin(LINES,COLS, 0, COLS - COLS/4);
  wvline(GAME_MENU, '#', LINES);
  refresh();
  return GAME_MENU;
}

//display the value of energy and whiffles the player currently has in menu
void display_EW(WINDOW * GAME_MENU, hero & player) {
  wmove(GAME_MENU, LINES - 3, 2);
  wclrtoeol(GAME_MENU);
  wprintw(GAME_MENU, "Whiffles: %d", player.whiffle);
  wmove(GAME_MENU, LINES - 2, 2);
  wclrtoeol(GAME_MENU);
  wprintw(GAME_MENU, "Energy: %d", player.energy);
  wmove(GAME_MENU, 0, 0);
  wvline(GAME_MENU, '#', LINES);
  refresh();
}

//displays movement options
void display_movement(WINDOW * GAME_MENU) {
  //menu start
  int y = 2;
  mvwprintw(GAME_MENU, y, 3, "1 to move left");
  mvwprintw(GAME_MENU, ++y, 3, "2 to move up");
  mvwprintw(GAME_MENU, ++y, 3, "3 to move right");
  mvwprintw(GAME_MENU, ++y, 3, "4 to move down");
  mvwprintw(GAME_MENU, ++y, 3, "5 to purchase");
}

bool tool_prompt(WINDOW * win) {
  mvwprintw(win, LINES/5 + 3, 2, "Would you like use a tool? y/n");
  bool ret = false;
  char input;
  wrefresh(win);

  while (input != 'y' && input != 'n') {

    cbreak();
    input = getch();
    wmove(win, LINES/5 + 4, 2);
    wclrtoeol(win);

    if (input == 'y') 
      ret = true;
    else if (input != 'n')
      mvwprintw(win, LINES/5 + 4, 2, "Invalid character please try again");
    wrefresh(win);
  }

  wmove(win, LINES/5 + 3, 2);
  wclrtoeol(win);
  wmove(win, LINES/5 + 4, 2);
  wclrtoeol(win);
  wrefresh(win);
  
  return ret;
}

void display_obstacle(WINDOW * GW, cell & c) { 
  int x,y;
  y = LINES/5;
  x = 2;
  mvwprintw(GW, y, x,"You have encountered a %s", c.obsType->name);
  mvwprintw(GW, ++y, x,"You need '%s' to destroy it", c.obsType->tool);
  wrefresh(GW);
}

void clearblock(WINDOW * GW, int start, int stop) {
  for(int i = 0; i < stop; ++i) {
    wmove(GW, start + i, 2);
    wclrtoeol(GW);
  }
    wrefresh(GW);
}

  
void display_cell(WINDOW * GAME_MENU, cell c){
  int x = 2;
  int y = LINES/4;
  y *= 3;
  
  curs_set(0);


  wmove(GAME_MENU, y, x);
  wprintw(GAME_MENU, "--GROVNIC INFO--");
  wmove(GAME_MENU, ++y, x);
  wclrtoeol(GAME_MENU);
  switch(c.symbol)
  {
    case '$':
       wprintw(GAME_MENU, ">TREASURE!!!<");
        break;

    case 'R':
        wprintw(GAME_MENU, ">ROYAL DIAMOND!!!<");
        break;

    case 'F':
        wprintw(GAME_MENU, ">FOOD: %s<", c.foodUnit->name);
        wmove(GAME_MENU, ++y, x);
        wclrtoeol(GAME_MENU);
        wprintw(GAME_MENU, ">COST: %s<", c.foodUnit->cost);
        wmove(GAME_MENU, ++y, x);
        wclrtoeol(GAME_MENU);
        wprintw(GAME_MENU, ">ENERGY: %s<", c.foodUnit->fill);

        break;

    case 'T':
        wprintw(GAME_MENU, ">TOOL: %s<", c.toolDevice->name);
        wmove(GAME_MENU, ++y, x);
        wclrtoeol(GAME_MENU);
        wprintw(GAME_MENU, ">COST: %s<", c.toolDevice->cost);
        wmove(GAME_MENU, ++y, x);
        wclrtoeol(GAME_MENU);
        wprintw(GAME_MENU, "%s", c.toolDevice->desc);

        break;

    case '!':
        wprintw(GAME_MENU, ">OBSTACLE: %s<", c.obsType->name);
        wmove(GAME_MENU, ++y, x);
        wclrtoeol(GAME_MENU);
        wprintw(GAME_MENU, ">ENERGY DRAIN: %s<", c.obsType->drain);
        wmove(GAME_MENU, ++y, x);
        wclrtoeol(GAME_MENU);
        wprintw(GAME_MENU, "TOOL NEEDED: %s", c.obsType->tool);

        break;

    case '?':
        wprintw(GAME_MENU,"CLUE");
        break;

    case 'S':
        wprintw(GAME_MENU,">SHIP<");

        break;
    case 'B':
        wprintw(GAME_MENU,">BINOCULARS<");

        break;
  }
}
