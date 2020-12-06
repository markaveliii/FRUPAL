#pragma once
#include <iostream>
#include <ncurses.h>
#include <fstream>

#define BINOCULARS 100

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

  tool();
  tool(const tool & source);
  void display(WINDOW * win, int y);       

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

class inventory
{
  public:
    inventory();
    ~inventory();
  
    int add_tool(tool & copy_from);
    //int remove_tool(char * to_delete);
    tool * retrieve_tool(int num);
    void display(WINDOW * win);
    void remove(int);

  protected:
    void initialize(tool ** &ptr, int size);
    int add_tool(tool ** &ptr, tool & copy_from);
    //int remove_tool(tool ** &inventory, char * to_delete);
    void delete_all(tool **& ptr);
    void display(WINDOW * win, tool ** ptr, int y, int count);

    tool ** backpack;
    int size;
};

// player
struct hero{
  int purchase_tool(tool * a_tool);
  int purchase_food(food * a_food);
  int purchase_ship();
  void use_tool(tool *, obstacle *);

  bool has_ship;
  int energy;
  int whiffle;
  int sight;
  int clue_counter;
  int x_pos;
  int y_pos;
  inventory backpack;
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
  char* clue;
  bool curs;
};
