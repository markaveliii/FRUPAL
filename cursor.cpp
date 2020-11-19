#include <curses.h>

int cursor(WINDOW *win)
{
    initscr();
    curs_set(2);
    nodelay(win, TRUE);
    noecho();
    keypad(win, TRUE);
    cbreak();
    int x = COLS/2;
    int y = LINES/2;
    wmove(win, y, x);
    int input;

    do{
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
    wmove(win, y, x);
    refresh();
    }while(input != 'q');
    endwin();
    
    return 0;
}
