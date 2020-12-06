#include "library.h"
#include "cstring"

tool::tool() {}

tool::tool(const tool & source) {

  strcpy(name, source.name);
  
  power = source.power;
  cost = source.cost;
}

void tool::display(WINDOW * win, int y) {
  wprintw(win,"%s\t lvl: %d",name, power);
   mvwprintw(win, y, 20, "lvl: %d", power);
}

int hero::purchase_tool(tool * a_tool) {
  whiffle -= a_tool->cost;
  if(whiffle >= 0) {
    backpack.add_tool(*a_tool);
  }
  else {
    whiffle += a_tool->cost;
    return 0;
  }
  return 1;
}

int hero::purchase_food(food * a_food) {
  whiffle -= a_food->cost;
  if (whiffle >= 0) {
    energy += a_food->fill;
  }
  else {
    whiffle += a_food->cost;
    return 0;
  }
  return 1;
}

int hero::purchase_ship() {
  whiffle -= 50;
  if(whiffle <= 0) {
    whiffle +=50;
    return 0;
  }
  return 1;
}

void hero::use_tool(tool * a_tool, obstacle * obs) {
  energy -= obs->drain/a_tool->power;
}

inventory::inventory() {
  size = 10;
  backpack = new tool*[size];
  tool ** ptr = backpack;
  initialize(ptr,size);
}

void inventory::initialize(tool ** &ptr, int size) {

  if(*ptr == *(backpack + (size + 1)))
   return;

  *ptr = NULL;
  
  return initialize(++ptr, size);

}

int inventory::add_tool(tool & copy_from) {

  tool ** ptr = backpack;
  return add_tool(ptr,copy_from);
}

int inventory::add_tool(tool ** &ptr, tool & copy_from){

  int success = 0;

  if(*ptr == *(backpack + (size + 1))) 
    return 0;

  if(!*ptr) {
    //copy copy from into tool via copy construct for easy use
    *ptr = new tool(copy_from);
    return 1;
  }
  
  return success += add_tool(++ptr, copy_from);
}

tool * inventory::retrieve_tool(int num) {
  return backpack[num];
}

void inventory::remove(int num) {
  if(backpack[num])
    delete backpack[num];
  backpack[num] = NULL;
}

void inventory::display(WINDOW * win) {
  
  tool ** ptr = backpack;
  wmove(win, LINES/2, 2);
  wprintw(win, "Tools");
  int y = LINES/2 + 1;
  int count = 1;
  return display(win, ptr, y, count);
}

void inventory::display(WINDOW * win, tool ** ptr, int y, int count) {

  if(*ptr == *(backpack + (size + 1)))
    return;

  if(*ptr) {
    mvwprintw(win, y, 2, "%d", count);
    wmove(win, y, 4);
    (*ptr)->display(win);
  }

  return display(win,++ptr, ++y, ++count);
}

   
inventory::~inventory() {

  tool ** ptr = backpack;
  delete_all(ptr);
  if(backpack)
    delete backpack;
  backpack = NULL;
}



void inventory::delete_all(tool **& ptr) {

  if(*ptr == *(backpack + (size + 1)))
    return;
  *ptr = NULL;
  return delete_all(++ptr);
}
