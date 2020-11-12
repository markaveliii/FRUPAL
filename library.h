#include <iostream>
#include <ncurses.h>
#include <fstream>

// player
struct hero{
  int energy;
  int whiffle;
};

struct obstacle{
  char* name;
  char* tool;
};

// food/tool
struct item{
  char* name;
  int cost;
  int fill;
};

// grovnick
struct cell{
  char tile;
  int drain;
  char symbol;
  bool visible;
  obstacle type;
  item unit;
  hero player;
};
