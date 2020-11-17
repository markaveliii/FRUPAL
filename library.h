#include <iostream>
#include <ncurses.h>
#include <fstream>

// player
struct hero{
  int energy;
  int whiffle;
  int x_pos;
  int y_pos;
  tool inventory[100];
};

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

// grovnick
struct cell{
  char tile;
  int drain;
  bool visible;
  bool exist;
  char symbol;
  int obsType;
  int foodUnit;
  int toolDevice;
  int treasureChest;
};
