#include <iostream>
#include <cmath>
#include <ncurses.h>
#include <libary.h>

using namespace std;
#define EMPTY      0
#define PLAYER     1
#define MEADOW     2
#define SWAMP      3
#define WATER      4
#define WALL       5
#define GOAL       6

int mapgen(cell island[128][128]);

int mapgen(cell island[128][128])
{
    int lengthx;
    int lengthy;
    int playerx = 0;
    int playery = 0;
    lengthx = COLS / 4;
    lengthx = lengthx * 3;
    lengthy = LINES / 4;
    lengthy = lengthy * 3;
    for(int x = 0; x < 129; x++){
        for(int y = 0; y < 129, y++){
            if(island[x][y].symbol == "@"){
                playerx = x;
                playery = y;
            }
        }
    }

    start_color();
    init_pair(EMPTY, COLOR_BLACK, COLOR_BLACK);
    init_pair(PLAYER, COLOR_BLACK, COLOR_RED);
    init_pair(MEADOW, COLOR_BLACK, COLOR_GREEN);
    init_pair(SWAMP, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(WATER, COLOR_BLACK, COLOR_BLUE);
    init_pair(WALL, COLOR_BLACK, COLOR_WHITE);
    init_pair(GOAL, COLOR_BLACK, COLOR_CYAN);

    for(int x = 0; x < lengthx + 1; x++){
        for(int y = 0; y < lengthy + 1, y++){
            attron(COLOR_PAIR(EMPTY));
            mvprintw(y,x," "); 
            attroff(COLOR_PAIR(EMPTY));   
        }
    }

    for(int x = playerx - lengthx; x < playerx + lengthx + 1; x++){
        for(int y = playery - lengthy; y < playery + legnthy +1, y++){
            if(-1 < x && x < 129 && -1 < y && y < 129){
                if(island[x][y].visible){
                    if(island[x][y].tile == "g"){
                        attron(COLOR_PAIR(MEADOW));
                        mvprintw(y,x,island[x][y].symbol); 
                        attroff(COLOR_PAIR(MEADOW));
                    }
                    if(island[x][y].tile == "s"){
                        attron(COLOR_PAIR(SWAMP));
                        mvprintw(y,x,island[x][y].symbol); 
                        attroff(COLOR_PAIR(SWAMP));
                    }
                    if(island[x][y].tile == "b"){
                        attron(COLOR_PAIR(WATER));
                        mvprintw(y,x,island[x][y].symbol); 
                        attroff(COLOR_PAIR(WATER));
                    }
                    if(island[x][y].tile == "w"){
                        attron(COLOR_PAIR(WALL));
                        mvprintw(y,x,island[x][y].symbol); 
                        attroff(COLOR_PAIR(WALL));
                    }
                    if(island[x][y].tile == "R"){
                        attron(COLOR_PAIR(GOAL));
                        mvprintw(y,x,island[x][y].symbol); 
                        attroff(COLOR_PAIR(GOAL));
                    }
                    if(island[x][y].symbol == "@"){
                        attron(COLOR_PAIR(PLAYER));
                        mvprintw(y,x,island[x][y].symbol); 
                        attroff(COLOR_PAIR(PLAYER));
                    }
                }
            }
        }
    }






    refresh();
    return 1;
}