//takes one quarter (most to the right) and creates a window that handles the game menu
WINDOW * create_game_menu() {
  WINDOW * GAME_MENU = newwin(LINES,COLS, 0, COLS-COLS/4);
  refresh();
  wvline(GAME_MENU, '#', LINES);
  return GAME_MENU;
}

//display the value of energy and whiffles the player currently has in menu
void display_EW(WINDOW * GAME_MENU, hero & player) {
  wmove(GAME_MENU, LINES - 3, 2);
  wclrtoeol(GAME_MENU);
  wprintw(GAME_MENU, "Whiffles: %d", player.cash);
  wmove(GAME_MENU, LINES - 2, 2);
  wclrtoeol(GAME_MENU);
  wprintw(GAME_MENU, "Energy: %d", player.energy);
}

void display_cell(WINDOW * GAME_MENU, cell c){
  int x = 2;
  int y = 1;
  
  if(!c.visible)
      return;
 
  wmove(GAME_MENU, y, x);
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
