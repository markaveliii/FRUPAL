#include "map.h"

using namespace std;
#define EMPTY      0
#define PLAYER     1
#define MEADOW     2
#define SWAMP      3
#define WATER      4
#define WALL       5
#define GOAL       6
#define HIGHLIGHT  7

int mapgen(cell island[128][128], hero & player)
{
    int lengthx;
    int lengthy;
    int i = 0;
    int j = 0;
    int playerx = player.y_pos;
    int playery = player.x_pos;
    lengthx = COLS / 4;
    lengthx = lengthx * 3;
    lengthy = LINES;


    start_color();
    init_pair(EMPTY, COLOR_BLACK, COLOR_BLACK);
    init_pair(PLAYER, COLOR_BLACK, COLOR_RED);
    init_pair(MEADOW, COLOR_BLACK, COLOR_GREEN);
    init_pair(SWAMP, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(WATER, COLOR_BLACK, COLOR_BLUE);
    init_pair(WALL, COLOR_BLACK, COLOR_WHITE);
    init_pair(GOAL, COLOR_BLACK, COLOR_CYAN);
    init_pair(HIGHLIGHT, COLOR_BLACK, COLOR_WHITE);


    //voids out previous screen
    for(int x = 0; x < lengthx + 1; x++){
        for(int y = 0; y < lengthy + 1; y++){
            attron(COLOR_PAIR(EMPTY));
            mvprintw(y,x," "); 
            attroff(COLOR_PAIR(EMPTY));   
        }
    }

    //colors in the map 
    for(int x = playery - (lengthx/2); x < playery + (lengthx/2) + 1; x++){
        for(int y = playerx - (lengthy/2); y < playerx + (lengthy/2) +1; y++){
            if(-1 < x && x < 129 && -1 < y && y < 129){
                if(island[y][x].visible){
                    switch(island[y][x].tile){
                        case 'g':
                            attron(COLOR_PAIR(MEADOW));
                            switch(island[y][x].symbol){
                                case '/':
                                    mvaddch(j,i,' ');
                                    break;
                                default:
                                    mvaddch(j,i,island[y][x].symbol);
                                    break;  
                            }
                            attroff(COLOR_PAIR(MEADOW));
                            break;
                        case 's':
                            attron(COLOR_PAIR(SWAMP));
                            switch(island[y][x].symbol){
                                case '/':
                                    mvaddch(j,i,' ');
                                    break;
                                default:
                                    mvaddch(j,i,island[y][x].symbol);
                                    break;  
                            }
                            attroff(COLOR_PAIR(SWAMP));
                            break;
                        case 'b':
                            attron(COLOR_PAIR(WATER));
                            switch(island[y][x].symbol){
                                case '/':
                                    mvaddch(j,i,' ');
                                    break;
                                default:
                                    mvaddch(j,i,island[y][x].symbol);
                                    break;  
                            } 
                            attroff(COLOR_PAIR(WATER));
                            break;
                        case 'w':
                            attron(COLOR_PAIR(WALL));
                            switch(island[y][x].symbol){
                                case '/':
                                    mvaddch(j,i,' ');
                                    break;
                                default:
                                    mvaddch(j,i,island[y][x].symbol);
                                    break;  
                            } 
                            attroff(COLOR_PAIR(WALL));
                            break;
                        /*case 'R':
                            attron(COLOR_PAIR(GOAL));
                            switch(island[y][x].symbol){
                                case '/':
                                    mvaddch(j,i,' ');
                                    break;
                                default:
                                    mvaddch(j,i,island[y][x].symbol);
                                    break;  
                            } 
                            attroff(COLOR_PAIR(GOAL));
                            break; */
                    }

                    if(y == playerx && x == playery){
                        attron(COLOR_PAIR(PLAYER));
                        mvaddch(j,i,'@'); 
                        attroff(COLOR_PAIR(PLAYER));
                    }
                    if(island[y][x].curs == true){
                        attron(A_BLINK);
                        attron(COLOR_PAIR(HIGHLIGHT));
                        if(island[y][x].symbol == '/')
                            mvaddch(j, i, ' ');
                        else
                            mvaddch(j, i, island[y][x].symbol);
                        attroff(COLOR_PAIR(HIGHLIGHT));
                        attroff(A_BLINK);
                    }

                    if(island[y][x].symbol == 'R'){
                        if(player.clue_counter <= 0){
                            attron(COLOR_PAIR(GOAL));
                            mvaddch(j,i,'$'); 
                            attroff(COLOR_PAIR(GOAL));
                        }
                    }

                }
            }
            j++;
        }
        j = 0;
        i++;
    }






    refresh();
    return 1;
}
