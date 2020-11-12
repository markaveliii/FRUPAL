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

// treasure chests
struct treasure{
  int whiffle;
  item* loot;
};

// grovnick
struct cell{
  char tile;
  int drain;
  bool visible;
  char symbol;
  obstacle type;
  item unit;
  treasure chest;
  hero player;
};
