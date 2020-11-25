#include <iostream>
#include <ncurses.h>
#include <fstream>

struct obstacle{
  char name[100];
  char tool[100];
  int drain;
};

struct food{
  char name[100];
  int cost;
  int fill;
};

struct tool{
  char name[100];
  int power;
  int cost;
  char desc[200];
};

struct treasure{
  int whiffle;
  food loot1[100];
  tool loot2[100];
};

// player
struct hero{
  int energy;
  int cash;
  int x_pos;
  int y_pos;
  tool inventory[100];
};

// cursor
struct cursor{
  int x_pos;
  int y_pos;
};

// grovnick
struct cell{
  char tile;
  int drain;
  bool visible;
  bool exist;
  char symbol;
  int objSelect;
  obstacle* obsType;
  food* foodUnit;
  tool* toolDevice;
  treasure* treasureChest;
};
