#include <curses.h>
#include <iostream>
#include "library.h"

int movement(cell map[128][128], hero &);
int purchase(cell &);
int cursor(WINDOW *w);
