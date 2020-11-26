#include "UI.h"

int movement(cell map[128][128], hero &p)
{
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    cell dest;

    switch(getch())
    {
        //Move left
        case 1:
            if(p.x_pos == 0)
                return 0;
            dest = map[p.y_pos][p.x_pos - 1];
            //Returns on failure if there's a wall and consumes energy.
            if(dest.tile == 'w' || dest.tile == 'b'){
                --p.energy;
                return 0;
            }
            //Handles obstacles
            if(dest.symbol == '!'){
                p.energy -= dest.obsType->drain;
            }
            else{
            p.energy -= dest.drain;
            }

            //update player location to (y,x-1)
            --p.x_pos;
            break;

        //Move Up
        case 2:
            if(p.y_pos == 0)
                return 0;
            dest = map[p.y_pos - 1][p.x_pos];
            //Returns on failure if there's a wall and consumes energy.
            if(dest.tile == 'w' || dest.tile == 'b'){
                --p.energy;
                return 0;
            }
            //Handles obstacles
            if(dest.symbol == '!'){
                p.energy -= dest.obsType->drain;
            }
            else{
            p.energy -= dest.drain;
            }

            //update player location to (y-1,x)
            --p.y_pos;
            break;

        //Move Right
        case 3:
            if(p.x_pos == COLS)
                return 0;
            dest = map[p.y_pos][p.x_pos + 1];

            //Returns on failure if there's a wall and consumes energy.
            if(dest.tile == 'w' || dest.tile == 'b'){
                --p.energy;
                return 0;
            }
            //Handles obstacles
            if(dest.symbol == '!'){
                p.energy -= dest.obsType->drain;
            }
            else{
            p.energy -= dest.drain;
            }

            //update player location to (y,x+1)
            ++p.x_pos;
            break;

        //Move down
        case 4:
            if(p.y_pos == LINES)
                return 0;
            dest = map[p.y_pos + 1][p.x_pos];

            //Returns on failure if there's a wall and consumes energy.
            if(dest.tile == 'w' || dest.tile == 'b'){
                --p.energy;
                return 0;
            }
            //Handles obstacles
            if(dest.symbol == '!'){
                p.energy -= dest.obsType->drain;
            }
            else{
                p.energy -= dest.drain;
            }

            //update player location to (y+1,x)
            ++p.y_pos;
            break;

    } 
    return 1;
}

/*int purchase(cell &dest)
{
    int cost;
    return cost;
}
*/