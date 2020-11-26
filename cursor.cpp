#include "UI.h"

int cursor(WINDOW * win, WINDOW * GAME_MENU, cell map[128][128], cursor &c)
{
    initscr();
    curs_set(2);
    nodelay(win, TRUE);
    noecho();
    keypad(win, TRUE);
    cbreak();

    int input;

    input = getch();
    switch(input)
    {
        case KEY_UP:
            if(y == 0)
                break;
            --c.y_pos;
            break;
        case KEY_DOWN:
            if(y == LINES-1)
                break;
            ++c.y_pos;
            break;
        case KEY_LEFT:
            if(x == 0)
                break;
            --c.x_pos;
            break;
        case KEY_RIGHT:
            if(x == COLS-1)
                break;
            ++c.x_pos;
            break;

    }


    display_cursor(win, c);
    if(map[c.y_pos][c.x_pos].visible){
        display_cell(GAME_MENU, map[c.y_pos][c.x_pos]);
    }
    refresh();
    
    return 0;
}

void display_cursor(WINDOW * win, cursor curs)
{
    wmove(win, curs.y_pos, curs.x_pos);
}
