#include <curses.h>
#include <iostream>
#include "library.h"

int movement(cell map[128][128], hero &);
int purchase(cell &);
int move_cursor(WINDOW *, WINDOW *, cell map[128][128], cursor &);
void display_cursor(WINDOW *, cursor);
