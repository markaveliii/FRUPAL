#include "library.h"

using namespace std;

int visitArea(cell island[128][128], hero& player){
  // range of sight
  int range = (((2 * player.sight) + 1) + 1) / 2;
  int curr_y = player.y_pos;
  int curr_x = player.x_pos;

  
  int x = 0, y = 0;

  // proceed to the left
  while((curr_x - x) >= 0 && x != range){
    island[curr_y][curr_x - x].visible = true;
    ++x;
  }

  // upper left bound
  x = 0; y = 0;
  while((curr_y - y) >= 0 && y != range){
    x = 0;
    // proceed upwards
    island[curr_y - y][curr_x].visible = true;
    // proceed to the left
    while((curr_x - x) >= 0 && x != range){
      island[curr_y - y][curr_x - x].visible = true;
      ++x;
    }
    ++y;
  }

  // lower left bound
  x = 0; y = 0;
  while((curr_y + y) <= 127 && y != range){
    x = 0;
    // proceed upwards
    island[curr_y + y][curr_x].visible = true;
    // proceed to the left
    while((curr_x - x) >= 0 && x != range){
      island[curr_y + y][curr_x - x].visible = true;
      ++x;
    }
    ++y;
  }

  // right bound
  x = 0; y = 0;
  while((curr_x + x) <= 127 && x != range){
    island[curr_y][curr_x + x].visible = true;
    ++x;
  }

  // upper right bound
  x = 0; y = 0;
  while((curr_y - y) >= 0 && y != range){
    x = 0;
    // proceed upwards
    island[curr_y - y][curr_x].visible = true;
    // proceed to the right 
    while((curr_x + x) <= 127 && x != range){
      island[curr_y - y][curr_x + x].visible = true;
      ++x;
    }
    ++y;
  }

  // lower right bound
  x = 0; y = 0;
  while((curr_y + y) <= 127 && y != range){
    x = 0;
    // proceed downwards
    island[curr_y + y][curr_x].visible = true;
    // proceed to the right 
    while((curr_x + x) <= 127 && x != range){
      island[curr_y + y][curr_x + x].visible = true;
      ++x;
    }
    ++y;
  }

  return 0;
}
