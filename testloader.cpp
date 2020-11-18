#include "maploader.h"

using namespace std;

// comment out define statement not being tested
#define IMPORT
//#define EXPORT

int main(){
  // refresh random seed
  srand(time(NULL));
  cell kingdom[128][128];
  obstacle obsList[100];
  food foodList[100];
  tool toolList[100];
  treasure chestList[100];
  char* map = new char[100];

#ifdef IMPORT
/*
  char table[4] = {'g', 's', 'b', 'w'};

  // generate a random map
  for(int i = 0; i < 128; ++i){
    for(int j = 0; j < 128; ++j)
      kingdom[i][j].tile = table[rand() % 4];
  }
 */ 
  if(mapExport("map1.txt", kingdom, obsList, foodList, toolList, chestList) != 0){
    cout << "\nFailed to load map\n";
    exit(1);
  }

  // display generated map
  for(int i = 0; i < 128; ++i){
    for(int j = 0; j < 128; ++j)
      cout << kingdom[i][j].tile;
    cout << '\n';
  }

  // create a new file
  /*
  cout << "\nEnter map name to save into (must have .txt at end of name: ";
  cin >> map;
*/
  //if(mapImport(map, kingdom) != 0)
  if(mapImport("import.txt", kingdom, obsList, foodList, toolList, chestList) != 0)
    cout << "\nFile name already exists\n";
#endif // IMPORT

#ifdef EXPORT
/*
  cout << "\nEnter map name to load: ";
  cin >> map;
*/
  // load map into game
  if(mapExport("map1.txt", kingdom, obsList, foodList, toolList, chestList) != 0){
    cout << "\nFailed to load map\n";
    exit(1);
  }
  // display map
  for(int i = 0; i < 128; ++i){
    for(int j = 0; j < 128; ++j){
      cout << kingdom[i][j].exist;
    }
    cout << '\n';
  }
/*
  int i = 0;
  while(obsList[i].name[0] != '\0'){
    cout << obsList[i].name << ' ' << obsList[i].tool << ' ' << obsList[i].drain << '\n';
    ++i;
  }
  i = 0;
  while(foodList[i].name[0] != '\0'){
    cout << foodList[i].name << ' ' << foodList[i].cost << ' ' << foodList[i].fill << '\n';
    ++i;
  }
  i = 0;
  while(toolList[i].name[0] != '\0'){
    cout << toolList[i].name << ' ' << toolList[i].power << ' ' << toolList[i].cost << ' ' << toolList[i].desc << '\n';
    ++i;
  }
  i = 0;
  while(chestList[i].whiffle != -100){
    cout << chestList[i].whiffle << '\n';
    int k = 0;
    while(chestList[i].loot1[k].name[0] != '\0'){
      cout << ' ' << chestList[i].loot1[k].name << ": " << chestList[i].loot1[k].cost << ' ' << chestList[i].loot1[k].fill << '\n';
      ++k;
    }
    k = 0;
    while(chestList[i].loot2[k].name[0] != '\0'){
      cout << ' ' << chestList[i].loot2[k].name << ": " << chestList[i].loot2[k].power << ' ' << chestList[i].loot2[k].cost << ' ' << chestList[i].loot2[k].desc<< '\n';
      ++k;
    }
    ++i;
  }
*/
/*
  for(int i = 0; i < 128; ++i){
    for(int j = 0; j < 128; ++j){
      switch(kingdom[i][j].symbol){
        case '!':
          cout << obsList[kingdom[i][j].obsType].name << ' ' << obsList[kingdom[i][j].obsType].tool << ' ' << obsList[kingdom[i][j].obsType].drain << '\n';
          break;
        case 'F':
          cout << foodList[kingdom[i][j].foodUnit].name << ' ' << foodList[kingdom[i][j].foodUnit].cost << ' ' << foodList[kingdom[i][j].foodUnit].fill << '\n';
          break;
        case 'T':
          cout << toolList[kingdom[i][j].toolDevice].name << ' ' << toolList[kingdom[i][j].toolDevice].power << ' '
            << toolList[kingdom[i][j].toolDevice].cost << ' ' << toolList[kingdom[i][j].toolDevice].desc << '\n';
          break;
        case '$':
          cout << chestList[kingdom[i][j].treasureChest].whiffle;
          int k = 0;
          while(chestList[kingdom[i][j].treasureChest].loot1[k].name[0] != '\0'){
            cout << ' ' << chestList[kingdom[i][j].treasureChest].loot1[k].name;
            ++k;
          }
          k = 0;
          while(chestList[kingdom[i][j].treasureChest].loot2[k].name[0] != '\0'){
            cout << ' ' << chestList[kingdom[i][j].treasureChest].loot2[k].name;
            ++k;
          }
          cout << '\n';
          break;
      }
    }
  }
  */
#endif // EXPORT

  return 0;
}
