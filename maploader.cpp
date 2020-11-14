#include "maploader.h" 

using namespace std;

#define OBJ

// load map into game
int mapExport(const char* map, cell island[128][128]){
  ifstream file;
  file.open(map);

  // error in map file
  if(!file)
    return -1;

  // start grabbing the entire map
  for(int i = 0; i < 128; ++i){
    for(int j = 0; j < 128; ++j){
      // retrieve grovnick type
      file >> island[i][j].tile;

      // hide each tile
      island[i][j].visible = false;

      // translate grovnick tile info
      switch(island[i][j].tile){
        case 'g':
          island[i][j].drain = 1;
          break;
        case 's':
          island[i][j].drain = 2;
          break;
        case 'b':
          island[i][j].drain = 1;
          break;
        case 'w':
          island[i][j].drain = 0;
          break;
      }
    }
  }

  // grab symbol location
  char symbol;
  int x = 0;
  for(int i = 0; i < 128; ++i){
    for(int j = 0; j < 128; ++j){
      file >> island[i][j].symbol;
    }
  }

  file.close();

  return 0;
}

// save map to a file
int mapImport(const char* map, cell island[128][128]){
  // test if file name exists
  ofstream file(map, ios::out | ios::in);
  if(file.is_open())
    return -1;

  //create new file
  file.open(map);

  // start writing map onto file
  for(int i = 0; i < 128; ++i){
    for(int j = 0; j < 128; ++j){
      file << island[i][j].tile;
    }
    file << '\n';
  }

  file.close();

  return 0;
}
