#include "UI.h"

int movement(cell map[128][128], hero &p, int input)
{
  if(p.energy <= 0)
    return -1;
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, FALSE);
  cell dest;
  
  switch(input)
  {
    //Move left
    case 'a':
    case 'A':

      if(p.x_pos == 0)
        return 0;
      dest = map[p.y_pos][p.x_pos - 1];
      //handles if player exits ship
      if(p.has_ship == true && dest.tile != 'b') {
        p.has_ship = false;
        map[p.y_pos][p.x_pos].symbol = 'S';
      }
      //Returns on failure if there's a wall and consumes energy.
      if(dest.tile == 'w'){
          --p.energy;
          return 0;
      }
      //handles if theres water and if player has ship or not
      if(dest.tile == 'b' && dest.symbol != 'S') {
          if(!p.has_ship) {
            --p.energy;
            return 0;
          }
      }
      //Handles obstacles
      if(map[p.y_pos][p.x_pos].symbol == '!'){
        p.energy -= map[p.y_pos][p.x_pos].obsType->drain;
        map[p.y_pos][p.x_pos].obsType = NULL;
        map[p.y_pos][p.x_pos].symbol = '/';
      }
      else{
        p.energy -= dest.drain;
      }
   
      //update player location to (y,x-1)
      --p.x_pos;
      break;

      //Move Up
    case 'w':
    case 'W':
      if(p.y_pos == 0)
        return 0;
      dest = map[p.y_pos - 1][p.x_pos];
        //handles if player exits ship
      if(p.has_ship == true && dest.tile != 'b') {
        p.has_ship = false;
        map[p.y_pos][p.x_pos].symbol = 'S';
      }
      //Returns on failure if there's a wall and consumes energy.
      if(dest.tile == 'w'){
          --p.energy;
          return 0;
      }
      //handles if theres water and if player has ship or not
      if(dest.tile == 'b' && dest.symbol != 'S') {
          if(!p.has_ship) {
            --p.energy;
            return 0;
          }
      }
      //Handles obstacles
      if(map[p.y_pos][p.x_pos].symbol == '!'){
        p.energy -= map[p.y_pos][p.x_pos].obsType->drain;
        map[p.y_pos][p.x_pos].obsType = NULL;
        map[p.y_pos][p.x_pos].symbol = '/';
      }
      else{
        p.energy -= dest.drain;
      }
      //update player location to (y-1,x)
      --p.y_pos;
      break;

      //Move Right
    case 'd':
    case 'D':
      if(p.x_pos == 128)
        return 0;
      dest = map[p.y_pos][p.x_pos + 1];
       //handles if player exits ship
      if(p.has_ship == true && dest.tile != 'b') {
        p.has_ship = false;
        map[p.y_pos][p.x_pos].symbol = 'S';
      }
      //Returns on failure if there's a wall and consumes energy.
      if(dest.tile == 'w'){
          --p.energy;
          return 0;
      }
      //handles if theres water and if player has ship or not
      if(dest.tile == 'b' && dest.symbol != 'S') {
          if(!p.has_ship) {
            --p.energy;
            return 0;
          }
      }
      //Handles obstacles
      if(map[p.y_pos][p.x_pos].symbol == '!'){
        p.energy -= map[p.y_pos][p.x_pos].obsType->drain;
        map[p.y_pos][p.x_pos].obsType = NULL;
        map[p.y_pos][p.x_pos].symbol = '/';
      }
      else{
        p.energy -= dest.drain;
      }
      //update player location to (y,x+1)
      ++p.x_pos;
      break;

      //Move down
    case 's':
    case 'S':
      if(p.y_pos == 128)
        return 0;
      dest = map[p.y_pos + 1][p.x_pos];
       //handles if player exits ship
      if(p.has_ship == true && dest.tile != 'b') {
        p.has_ship = false;
        map[p.y_pos][p.x_pos].symbol = 'S';
      }
      //Returns on failure if there's a wall and consumes energy.
      if(dest.tile == 'w'){
          --p.energy;
          return 0;
      }
      //handles if theres water and if player has ship or not
      if(dest.tile == 'b' && dest.symbol != 'S') {
          if(!p.has_ship) {
            --p.energy;
            return 0;
          }
      }
      //Handles obstacles
      if(map[p.y_pos][p.x_pos].symbol == '!'){
        p.energy -= map[p.y_pos][p.x_pos].obsType->drain;
        map[p.y_pos][p.x_pos].obsType = NULL;
        map[p.y_pos][p.x_pos].symbol = '/';
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
