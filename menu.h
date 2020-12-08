//takes one quarter (most to the right) and creates a window that handles the game menu
WINDOW * create_game_menu() {
  WINDOW * GAME_MENU = newwin(LINES,COLS, 0, COLS - COLS/4);
  wvline(GAME_MENU, '#', LINES);
  refresh();
  return GAME_MENU;
}

//display the value of energy and whiffles the player currently has in menu
void display_EW(WINDOW * GAME_MENU, hero & player) {
  wmove(GAME_MENU, LINES/5 + 4, 2);
  wclrtoeol(GAME_MENU);
  mvprintw(12, (COLS - COLS/4) + 3, "Clues left: %d", player.clue_counter);
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
  mvwprintw(GAME_MENU, y, 3, "> A to move left");
  mvwprintw(GAME_MENU, ++y, 3, "> W to move up");
  mvwprintw(GAME_MENU, ++y, 3, "> D to move right");
  mvwprintw(GAME_MENU, ++y, 3, "> S to move down");
  mvwprintw(GAME_MENU, ++y, 3, "> p to purchase");
}
bool prompt(WINDOW * win) {
  bool ret = false;
  char input;
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

void purchase_success() {
  mvprintw(12, (COLS - COLS/4) + 3, "Purchase success");
  mvprintw(13, (COLS - COLS/4) + 3, "Press any key to continute.");
  getch();
  move(12, (COLS - COLS/4) + 3);
  clrtoeol();
  move(13, (COLS - COLS/4) + 3);
  clrtoeol();
  refresh();
}

void purchase_failed() {
  mvprintw(12, (COLS - COLS/4) + 3, "Not enough money :'(");
  mvprintw(13, (COLS - COLS/4) + 3, "Press any key to continute.");
  getch();
  move(12, (COLS - COLS/4) + 3);
  clrtoeol();
  move(13, (COLS - COLS/4) + 3);
  clrtoeol();
  refresh();
}

bool tool_prompt(WINDOW * win) {
  mvwprintw(win, LINES/5 + 3, 2, "Would you like use a tool? y/n");
  wrefresh(win);
  return prompt(win);
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


void display_cell(WINDOW * GAME_MENU, cell c, int clues){
  int x = 2;
  int y = LINES/4;
  y *= 3;

  curs_set(0);


  wmove(GAME_MENU, y, x);
  wprintw(GAME_MENU, "--GROVNIC INFO--");
  wmove(GAME_MENU, ++y, x);
  wclrtoeol(GAME_MENU);
  wmove(GAME_MENU, y+1, x);
  wclrtoeol(GAME_MENU);
  wmove(GAME_MENU, y+2, x);
  wclrtoeol(GAME_MENU);
  wmove(GAME_MENU, y+3, x);
  wclrtoeol(GAME_MENU);

  switch(c.symbol)
  {
    case '$':
      wprintw(GAME_MENU, ">TREASURE!!!<");
      wmove(GAME_MENU, ++y, x);
      wclrtoeol(GAME_MENU);
      wprintw(GAME_MENU, ">WHIFFLE: %d<", c.treasureChest->whiffle);
      wmove(GAME_MENU, ++y, x);
      wclrtoeol(GAME_MENU);
      wprintw(GAME_MENU, ">LOOT 1: %s<", c.treasureChest->loot1);
      wmove(GAME_MENU, ++y, x);
      wclrtoeol(GAME_MENU);
      wprintw(GAME_MENU, ">LOOT 2: %s<", c.treasureChest->loot2);



      break;

    case 'R':
      if(clues <= 0)
        wprintw(GAME_MENU, ">ROYAL DIAMOND!!!<");
      break;

    case 'F':
      wprintw(GAME_MENU, ">FOOD: %s<", c.foodUnit->name);
      wmove(GAME_MENU, ++y, x);
      wclrtoeol(GAME_MENU);
      wprintw(GAME_MENU, ">COST: %d<", c.foodUnit->cost);
      wmove(GAME_MENU, ++y, x);
      wclrtoeol(GAME_MENU);
      wprintw(GAME_MENU, ">ENERGY: %d<", c.foodUnit->fill);

      break;

    case 'T':
      wprintw(GAME_MENU, ">TOOL: %s<", c.toolDevice->name);
      wmove(GAME_MENU, ++y, x);
      wclrtoeol(GAME_MENU);
      wprintw(GAME_MENU, ">COST: %d<", c.toolDevice->cost);
      wmove(GAME_MENU, ++y, x);
      wclrtoeol(GAME_MENU);
      wprintw(GAME_MENU, "%s", c.toolDevice->desc);

      break;

    case '!':
      wprintw(GAME_MENU, ">OBSTACLE: %s<", c.obsType->name);
      wmove(GAME_MENU, ++y, x);
      wclrtoeol(GAME_MENU);
      wprintw(GAME_MENU, ">ENERGY DRAIN: %d<", c.obsType->drain);
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
      wmove(GAME_MENU, ++y, x);
      wclrtoeol(GAME_MENU);
      wprintw(GAME_MENU, ">COST: %d<", BINOCULARS);

      break;

    case '/':
      clearblock(GAME_MENU, y,6);
      wrefresh(GAME_MENU);
      break;
  }
}
