#include "UI.h"

int move_cursor(WINDOW * GAME, WINDOW * GAME_MENU, cell map[128][128], cursor &c)
{
    curs_set(2);
    nodelay(GAME, FALSE);
    noecho();
    keypad(GAME, TRUE);
    cbreak();

    int input;

    input = getch();
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
    
    return 0;
}

void display_cursor(WINDOW * win, cursor curs)
{
    wmove(win, curs.y_pos, curs.x_pos);
}
