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
