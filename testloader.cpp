//This program is to test the import/export feature from maploader.h
#include "maploader.h"

using namespace std;

// comment out define statement not being tested
//#define IMPORT
#define EXPORT
//#define INPUT

int main(){
  // refresh random seed
  srand(time(NULL));
  cell kingdom[128][128];
  char* map = new char[100];

#ifdef IMPORT
  char table[4] = {'g', 's', 'b', 'w'};

  // generate a random map
  for(int i = 0; i < 128; ++i){
    for(int j = 0; j < 128; ++j)
      kingdom[i][j].tile = table[rand() % 4];
  }
  
  // display generated map
  for(int i = 0; i < 128; ++i){
    for(int j = 0; j < 128; ++j)
      cout << kingdom[i][j].tile;
    cout << '\n';
  }

  // create a new file
  cout << "\nEnter map name to save into (must have .txt at end of name: ";
  cin >> map;

  if(mapImport(map, kingdom) != 0)
    cout << "\nFile name already exists\n";
#endif // IMPORT

#ifdef EXPORT
#ifdef INPUT
  cout << "\nEnter map name to load: ";
  cin >> map;
#endif // INPUT
  // load map into game
#ifdef INPUT
  if(mapExport(map, kingdom)){
     cout << "\nFailed to load map\n";
     exit(1);
  }  
#else
  if(mapExport("map1.txt", kingdom)){
    cout << "\nFailed to load map\n";
    exit(1);
  }
#endif // INPUT

  // display map
  for(int i = 0; i < 128; ++i){
    for(int j = 0; j < 128; ++j){
      cout << kingdom[i][j].tile;
    }
    cout << '\n';
  }
#endif // EXPORT

  return 0;
}
