#include "maploader.h" 

using namespace std;

// load map into game
int mapExport(const char* map, cell island[128][128], obstacle obsList[100], food foodList[100], tool toolList[100], treasure chestList[100], hero& player){
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

      // assume there are no objects
      island[i][j].exist = false;

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
  int x = 0;
  int objLocation[2][128*128];
  for(int i = 0; i < 128; ++i){
    for(int j = 0; j < 128; ++j){
      // grab symbol placement
      file >> island[i][j].symbol;
      switch(island[i][j].symbol){
        case '!':
          island[i][j].exist = true;
          objLocation[0][x] = i;
          objLocation[1][x] = j;
          ++x; 
          break;
        case 'F':
          island[i][j].exist = true;
          objLocation[0][x] = i;
          objLocation[1][x] = j;
          ++x;
          break;
        case 'T':
          island[i][j].exist = true;
          objLocation[0][x] = i;
          objLocation[1][x] = j;
          ++x;
          break;
        case '$':
          island[i][j].exist = true;
          objLocation[0][x] = i;
          objLocation[1][x] = j;
          ++x;
          break;
        case '@':
          player.x_pos = j;
          player.y_pos = i;
          break;
      }
    }
  }

  objLocation[0][x] = -100;

  int total[4];
  char text[100];

  // grab total of each section
  for(int i = 0; i < 4; ++i){
    file >> total[i];
    file.ignore(100, ':');
  }
  file.ignore(100, '\n');

  // fetch obstacles
  if(total[0] > 0){
    for(int i = 0; i < total[0]; ++i){
      // retrieve name
      file.getline(text, 100, ',');
      text[strlen(text)] = '\0';
      strcpy(obsList[i].name, text);

      // retrieve tool 
      file.getline(text, 100, ',');
      text[strlen(text)] = '\0';
      strcpy(obsList[i].tool, text);

      // retrieve drain
      file >> obsList[i].drain;
      file.ignore(100, ':');
    }
  }
  obsList[total[0]].name[0] = '\0';
  file.ignore(100, '\n');

  // fetch food
  if(total[1] > 0){
    for(int i = 0; i < total[1]; ++i){
      // retrieve name
      file.getline(text, 100, ',');
      text[strlen(text)] = '\0';
      strcpy(foodList[i].name, text);

      // retrieve cost of food
      file >> foodList[i].cost;
      file.ignore(100, ',');

      // retrieve energy refill value
      file >> foodList[i].fill;
      file.ignore(100, ':');
    }
  }
  foodList[total[1]].name[0] = '\0';
  file.ignore(100, '\n');
  
  // fetch tools
  if(total[2] > 0){
    for(int i = 0; i < total[2]; ++i){
      // retrieve name
      file.getline(text, 100, ',');
      text[strlen(text)] = '\0';
      strcpy(toolList[i].name, text);

      // retrieve tool's power
      file >> toolList[i].power;
      file.ignore(100, ',');

      // retrieve cost of tool
      file >> toolList[i].cost;
      file.ignore(100, ',');

      // retrieve tool description
      file.getline(text, 200, ':');
      text[strlen(text)] = '\0';
      strcpy(toolList[i].desc, text);
    }
  }
  toolList[total[2]].name[0] = '\0';
  file.ignore(100, '\n');

  // fetch treasures
  if(total[3] > 0){
    int countFood;
    int countTool;
    for(int i = 0; i < total[3]; ++i){
      // retrieve whiffle
      file >> chestList[i].whiffle;
      file.ignore(100, ',');
      // number of food in chest
      file >> countFood;
      file.ignore(100, ',');

      // number of tools in chest
      file >> countTool;
      file.ignore(100, ':');

      // retrieve food in chest
      if(countFood > 0){
        for(int j = 0; j < countFood; ++j){
          // last item of section
          if(j == (countFood - 1)){
            file.getline(text, 100, ':');
            text[strlen(text)] = '\0';
          }
          // not the last
          else{
            file.getline(text, 100, ',');
            text[strlen(text)] = '\0';
          }

          // search for food loot in food list
          int n = 0;
          while(n < total[1]){
            if(strcmp(text, foodList[n].name) == 0)
              chestList[i].loot1[j] = foodList[n];
            ++n;
          }
        }
        chestList[i].loot1[countFood].name[0] = '\0';
      }

      // retrieve tools in chest
      if(countTool > 0){
        for(int j = 0; j < countTool; ++j){
          // last item of section
          if(j == (countTool - 1)){
            file.getline(text, 100, ':');
            text[strlen(text)] = '\0';
          }
          // not the last
          else{
            file.getline(text, 100, ',');
            text[strlen(text)] = '\0';
          }

          // search for tool loot in tool list
          int n = 0;
          while(n < total[2]){
            if(strcmp(text, toolList[n].name) == 0)
              chestList[i].loot2[j] = toolList[n];
            ++n;
          }
        }
        chestList[i].loot2[countTool].name[0] = '\0';
      }
    }
  }
  chestList[total[3]].whiffle = -100;

  // place obstacles/items/chests in location
  int select;
  int count;
  for(int i = 0; i < x; ++ i){
    int objY = objLocation[0][i];
    int objX = objLocation[1][i];
    
    file >> count;
    file.ignore(100, ',');
    file >> select;
    file.ignore(100, ':');
    
    switch(count){
      case 1:
        island[objY][objX].objSelect = select;
        island[objY][objX].obsType = &obsList[select];
        island[objY][objX].foodUnit = NULL;
        island[objY][objX].toolDevice = NULL;
        island[objY][objX].treasureChest = NULL;
        break;
      case 2:
        island[objY][objX].objSelect = select;
        island[objY][objX].foodUnit = &foodList[select];
        island[objY][objX].obsType = NULL;
        island[objY][objX].toolDevice = NULL;
        island[objY][objX].treasureChest = NULL;
        break;
      case 3:
        island[objY][objX].objSelect = select;
        island[objY][objX].toolDevice = &toolList[select];
        island[objY][objX].obsType = NULL;
        island[objY][objX].foodUnit = NULL;
        island[objY][objX].treasureChest = NULL;
        break;
      case 4:
        island[objY][objX].objSelect = select;
        island[objY][objX].treasureChest = &chestList[select];
        island[objY][objX].obsType = NULL;
        island[objY][objX].foodUnit = NULL;
        island[objY][objX].toolDevice = NULL;
        break;
    }
  }

  file.close();

  return 0;
}

// save map to a file
int mapImport(const char* map, cell island[128][128], obstacle obsList[100], food foodList[100], tool toolList[100], treasure chestList[100]){
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

  // start writing object placement onto file
  int objLocation[2][128*128];
  int x = 0;
  for(int i = 0; i < 128; ++i){
    for(int j = 0; j < 128; ++j){
      file << island[i][j].symbol;

      // store object selections
      switch(island[i][j].symbol){
        case '!':
          objLocation[0][x] = 1;
          objLocation[1][x] = island[i][j].objSelect;
          ++x; 
          break;
        case 'F':
          objLocation[0][x] = 2;
          objLocation[1][x] = island[i][j].objSelect;
          ++x;
          break;
        case 'T':
          objLocation[0][x] = 3;
          objLocation[1][x] = island[i][j].objSelect;
          ++x;
          break;
        case '$':
          objLocation[0][x] = 4;
          objLocation[1][x] = island[i][j].objSelect;
          ++x;
          break;
      }
    }
    file << '\n';
  }
  objLocation[0][x] = -100;

  // store total obstacles
  int total[4] = {0};
  while(obsList[total[0]].name[0] != '\0')
    ++total[0];
  file << total[0] << ':';
  // store total food
  while(foodList[total[1]].name[0] != '\0')
    ++total[1];
  file << total[1] << ':';
  // store total tools
  while(toolList[total[2]].name[0] != '\0')
    ++total[2];
  file << total[2] << ':';
  // store total treasures
  while(chestList[total[3]].whiffle >= 0)
    ++total[3];
  file << total[3] << ':' << '\n';

  // store all obstacles
  for(int i = 0; i < total[0]; ++i){
    file << obsList[i].name << ',';
    file << obsList[i].tool << ',';
    file << obsList[i].drain << ':';
  }
  file << '\n';

  // store all food
  for(int i = 0; i < total[1]; ++i){
    file << foodList[i].name << ',';
    file << foodList[i].cost << ',';
    file << foodList[i].fill << ':';
  }
  file << '\n';

  // store all tools
  for(int i = 0; i < total[2]; ++i){
    file << toolList[i].name << ',';
    file << toolList[i].power << ',';
    file << toolList[i].cost << ',';
    file << toolList[i].desc << ':';
  }
  file << '\n';

  // store all treasures
  for(int i = 0; i < total[3]; ++i){
    file << chestList[i].whiffle << ',';

    // store total food loot
    int lootTotal[2];
    char foodTemp[20][100];
    char toolTemp[20][100];
    int k = 0;
    while(chestList[i].loot1[k].name[0] != '\0'){
      strcpy(foodTemp[k], chestList[i].loot1[k].name);
      ++k;
    }
    foodTemp[k][0] = '\0';
    lootTotal[0] = k;
    file << k << ',';

    // store total tool loot
    k = 0;
    while(chestList[i].loot2[k].name[0] != '\0'){
      strcpy(toolTemp[k], chestList[i].loot2[k].name);
      ++k;
    }
    toolTemp[k][0] = '\0';
    lootTotal[1] = k;
    file << k << ':';
    
    // store loot
    k = 0;
    while(foodTemp[k][0] != '\0'){
      if(k == (lootTotal[0] - 1))
        file << foodTemp[k] << ':';
      else
        file << foodTemp[k] << ',';
      ++k;
    }
    k = 0;
    while(toolTemp[k][0] != '\0'){
      if(k == (lootTotal[1] - 1))
        file << toolTemp[k] << ':';
      else
        file << toolTemp[k] << ',';
      ++k;
    }
  }
  file << '\n';

  // store object placement
  x = 0;
  while(objLocation[0][x] >= 0){
    file << objLocation[0][x] << ',';
    file << objLocation[1][x] << ':';
    ++x;
  }

  file.close();

  return 0;
}
