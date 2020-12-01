#include "UI.h"
#ifndef __LIBRARY__
#include "library.h"
#endif

int move_cursor(WINDOW * GAME, WINDOW * GAME_MENU, cell map[128][128], cursor &c, int input)
{
    nodelay(GAME, FALSE);
    noecho();
    keypad(GAME, TRUE);
    cbreak();
    curs_set(2);

    wrefresh(GAME);
    switch(input)
    {
        case KEY_UP:
            if(c.y_pos == 0)
                break;
            --c.y_pos;
            break;
        case KEY_DOWN:
            if(c.y_pos == 128-1)
                break;
            ++c.y_pos;
            break;
        case KEY_LEFT:
            if(c.x_pos == 0)
                break;
            --c.x_pos;
            break;
        case KEY_RIGHT:
            if(c.x_pos ==  128-1)
                break;
            ++c.x_pos;
            break;

    }

    return 0;
}

void display_cursor(WINDOW * win, cursor curs, cell t)
{
    curs_set(2);
/*    start_color();
    init_pair(9, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(9));
    mvprintw(curs.y_pos-LINES, curs.x_pos-COLS, " ");
    attroff(COLOR_PAIR(9));
*/
    wmove(win, curs.y_pos/4, curs.x_pos/3);
}
