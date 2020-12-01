// Benjamin Lostheart CS300 
#include "library.h"
#include "cstring"

tool::tool() {}

tool::tool(const tool & source) {

  strcpy(name, source.name);
  
  power = source.power;
  cost = source.cost;
}

void tool::display(WINDOW * win) {
  wprintw(win,"%s\t lvl: %d",name, power);
}

void hero::purchase_tool(tool * a_tool) {
  whiffle -= a_tool->cost;
  backpack.add_tool(*a_tool);
  mvprintw(12, (COLS - COLS/4) + 3, "Purchase success");
  mvprintw(13, (COLS - COLS/4) + 3, "Press any key to continute.");
  getch();
  move(12, (COLS - COLS/4) + 3);
  clrtoeol();
  move(13, (COLS - COLS/4) + 3);
  clrtoeol();
  refresh();
}

void hero::purchase_food(food * a_food) {
  whiffle -= a_food->cost;
  energy += a_food->fill;
  mvprintw(15, (COLS - COLS/4) + 3, "Purchase success");
  mvprintw(16, (COLS - COLS/4) + 3, "Press any key to continute.");
  getch();
  move(15, (COLS - COLS/4) + 3);
  clrtoeol();
  move(16, (COLS - COLS/4) + 3);
  clrtoeol();
}
  
inventory::inventory() {
  size = 4;
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

void inventory::display(WINDOW * win) {
  
  tool ** ptr = backpack;
  wmove(win, LINES/4 + 7, 3);
  wprintw(win, "Tools");
  int y = LINES/4 + 8;
  return display(win, ptr, y);
}

void inventory::display(WINDOW * win, tool ** ptr, int y) {

  if(*ptr == *(backpack + (size + 1)))
    return;

  if(*ptr) {
    wmove(win, y, 3);
    (*ptr)->display(win);
  }

  return display(win,++ptr, ++y);
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
  

    
