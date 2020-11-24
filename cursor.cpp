#include "UI.h"

int cursor(WINDOW * win, WINDOW * GAME_MENU, cell * map)
{
    initscr();
    curs_set(2);
    nodelay(win, TRUE);
    noecho();
    keypad(win, TRUE);
    cbreak();

    int input;
    int x = COLS/2;
    int y = LINES/2;
    cell dest;

    wmove(win, y, x);
    input = getch();
    switch(input)
    {
        case KEY_UP:
            if(y == 0)
                break;
            --y;
            break;
        case KEY_DOWN:
            if(y == LINES-1)
                break;
            ++y;
            break;
        case KEY_LEFT:
            if(x == 0)
                break;
            --x;
            break;
        case KEY_RIGHT:
            if(x == COLS-1)
                break;
            ++x;
            break;

    }


    display_cursor(win, curs);
    dest = map[y][x];
    display_cell(GAME_MENU, dest);
    refresh();
    
    return 0;
}

void display_cursor(WINDOW * win, cursor curs)
{
    wmove(win, y, x);
}
