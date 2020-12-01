#include "UI.h"
#ifndef __LIBRARY__
#include "library.h"
#endif

int move_cursor(WINDOW * GAME, WINDOW * GAME_MENU, cell map[128][128], cursor &c, int input)
{
    curs_set(2);
    nodelay(GAME, FALSE);
    noecho();
    keypad(GAME, TRUE);
    cbreak();

    switch(input)
    {
        case KEY_UP:
            if(c.y_pos == 0)
                break;
            --c.y_pos;
            break;
        case KEY_DOWN:
            if(c.y_pos == LINES-1)
                break;
            ++c.y_pos;
            break;
        case KEY_LEFT:
            if(c.x_pos == 0)
                break;
            --c.x_pos;
            break;
        case KEY_RIGHT:
            if(c.x_pos ==  COLS-1)
                break;
            ++c.x_pos;
            break;

    }


    display_cursor(GAME, c);
    if(map[c.y_pos][c.x_pos].visible){
        //display_cell(GAME_MENU, map[c.y_pos][c.x_pos]);
    }
    wrefresh(GAME);
    
    return 0;
}

void display_cursor(WINDOW * win, cursor curs)
{
    wmove(win, curs.y_pos, curs.x_pos);
}
