#include "randmap.h"

int mapRandom(cell island[128][128], obstacle obsList[100], food foodList[100], tool toolList[100], treasure chestList[100], hero& player){
  // load all objects
  if(mapExport("random.txt", island, obsList, foodList, toolList, chestList, player) != 0)
    return -1;

  // spawn player randomly
  player.x_pos = rand() % 126 + 1;
  player.y_pos = rand() % 126 + 1;

  island[player.y_pos][player.x_pos].symbol = '@';
  int x = player.x_pos;
  int y = player.y_pos;


  // start creating paths
  for(int i = 0; i < PATH; ++i){
    // determine where to create a path
    int direction = rand() % 4 + 1;
    int distance = rand() % 64 + 1;
    int width = rand() % 5 + 3;

    switch(direction){
      case 1:
        if(y <= 1)
          direction = rand() % 3 + 2;
        break;
      case 2:
        if(y >= 126){
          while(direction == 2)
            direction = rand() % 4 + 1;
        }
        break;
      case 3:
        if(x <= 1){
          while(direction == 3)
            direction = rand() % 4 + 1;
        }
        break;
      case 4:
        if(x >= 126)
          direction = rand() % 3 + 1;
        break;
    }

    // create a path
    int j = 0;
    switch(direction){
      // up
      case 1:
        while(j < distance && (y - j) >= 1){
          island[y - j][x].tile = 'g';
          island[y - j][x].drain = 1;

          if((x - width) >= 1){
            for(int l = 0; l < width; ++l){
              island[y - j][x - l].tile = 'g';
              island[y - j][x - l].drain = 1;
            }
          }
          else if((x + width) <= 126){
            for(int l = 0; l < width; ++l){
              island[y - j][x + l].tile = 'g';
              island[y - j][x + l].drain = 1;
            }
          }

          ++j;
        }
        y -= (j - 1);
        break;
        // down
      case 2:
        while(j < distance && (y + j) <= 126){
          island[y + j][x].tile = 'g';
          island[y + j][x].drain = 1;

          if((x - width) >= 1){
            for(int l = 0; l < width; ++l){
              island[y - j][x - l].tile = 'g';
              island[y - j][x - l].drain = 1;
            }
          }
          else if((x + width) <= 126){
            for(int l = 0; l < width; ++l){
              island[y - j][x + l].tile = 'g';
              island[y - j][x + l].drain = 1;
            }
          }

          ++j;
        }
        y += (j - 1);
        break;
        // left
      case 3:
        while(j < distance && (x - j) >= 1){
          island[y][x - j].tile = 'g';
          island[y][x - j].drain = 1;

          if((y - width) >= 1){
            for(int l = 0; l < width; ++l){
              island[y - l][x - j].tile = 'g';
              island[y - l][x - j].drain = 1;
            }
          }
          else if((y + width) <= 126){
            for(int l = 0; l < width; ++l){
              island[y - l][x + j].tile = 'g';
              island[y - l][x + j].drain = 1;
            }
          }

          ++j;
        }
        x -= (j - 1);
        break;
        // right
      case 4:
        while(j < distance && (x + j) <= 126){
          island[y][x + j].tile = 'g';
          island[y][x + j].drain = 1;

          if((y - width) >= 1){
            for(int l = 0; l < width; ++l){
              island[y - l][x - j].tile = 'g';
              island[y - l][x - j].drain = 1;
            }
          }
          else if((y + width) <= 126){
            for(int l = 0; l < width; ++l){
              island[y - l][x + j].tile = 'g';
              island[y - l][x + j].drain = 1;
            }
          }

          ++j;
        }
        x += (j - 1);
        break;
    }
  }

  // place swamps
  x = rand() % 126 + 1;
  y = rand() % 126 + 1;
  for(int i = 0; i < SWAMPS; ++i){
    while(island[y][x].tile != 'g'){
      x = rand() % 127 + 1;
      y = rand() % 127 + 1;
    }

    int length = rand() % 20 + 1;
    int width = rand() % 20 + 1;

    for(int j = 0; j < length; ++j){
      for(int l = 0; l < width; ++l){
        if(island[y - j][x - l].tile != 'g')
          break;
        else{
          island[y - j][x - l].tile = 's';
          island[y - j][x - l].drain = 2;
        }
      }
    }
  }

  // clear edges with walls
  for(int i = 0; i < 128; ++i){
    island[0][i].tile = 'w';
    island[127][i].tile = 'w';
    island[i][0].tile = 'w';
    island[i][127].tile = 'w';
  }

  // grab total of each object category
  int obs = 0, foods = 0, tools = 0, chests = 0;
  while(obsList[obs].name[0] != '\0')
    ++obs;
  while(foodList[foods].name[0] != '\0')
    ++foods;
  while(toolList[tools].name[0] != '\0')
    ++tools;
  while(chestList[chests].whiffle >= 0)
    ++chests;

  // place obstacles
  for(int i = 0; i < OBS; ++i){
    int select = 0;
    x = 2 + (2 * rand()) % 128;
    y = 2 + (2 * rand()) % 128;
    while(island[y][x].tile == 'w' || island[y][x].symbol != '/'){
      x = rand()% 128;
      y = rand()% 128;
    }

    island[y][x].symbol = '!';
    select = rand() % obs;
    island[y][x].obsType = &obsList[select];
    island[y][x].objSelect = select;
  }

  // place foods
  for(int i = 0; i < FOODS; ++i){
    int select = 0;
    x = 2 + (2 * rand()) % 128;
    y = 2 + (2 * rand()) % 128;
    while(island[y][x].tile == 'w' || island[y][x].symbol != '/'){
      x = rand()% 128;
      y = rand()% 128;
    }

    island[y][x].symbol = 'F';
    select = rand() % foods;
    island[y][x].foodUnit = &foodList[select];
    island[y][x].objSelect = select;
  }

  // place tools
  for(int i = 0; i < TOOLS; ++i){
    int select = 0;
    x = 2 + (2 * rand()) % 128;
    y = 2 + (2 * rand()) % 128;
    while(island[y][x].tile == 'w' || island[y][x].symbol != '/'){
      x = rand()% 128;
      y = rand()% 128;
    }
    island[y][x].symbol = 'T';
    select = rand() % obs;
    island[y][x].toolDevice = &toolList[select];
    island[y][x].objSelect = select;
  }

  // place chests
  for(int i = 0; i < CHESTS; ++i){
    int select = 0;
    x = 2 + (2 * rand()) % 128;
    y = 2 + (2 * rand()) % 128;
    while(island[y][x].tile == 'w' || island[y][x].symbol != '/'){
      x = rand()% 128;
      y = rand()% 128;
    }
    island[y][x].symbol = '$';
    select = rand() % chests;
    island[y][x].treasureChest = &chestList[select];
    island[y][x].objSelect = select;
  }
  // place clues
  x = rand() % 128;
  y = rand() % 128;
  for(int i = 0; i < CLUES; ++i){
    while((island[y][x].tile != 'g' && island[y][x].tile != 's') || island[y][x].symbol != '/'){
      x = rand() % 128;
      y = rand() % 128;
    }
    island[y][x].symbol = '?';
  }
  player.clue_counter = CLUES;

  // place binoculars
  x = rand() % 128;
  y = rand() % 128;
  for(int i = 0; i < BINO; ++i){
    while((island[y][x].tile != 'g' && island[y][x].tile != 's') || island[y][x].symbol != '/'){
      x = rand() % 128;
      y = rand() % 128;
    }
    island[y][x].symbol = 'B';
  }

  // place royal diamond
  x = rand() % 128;
  y = rand() % 128;
  while(island[y][x].symbol != '/' && (island[y][x].tile == 'g' || island[y][x].tile == 's')){
    x = rand() % 128;
    y = rand() % 128;
  }
  island[y][x].symbol = 'R';

  island[player.y_pos][player.x_pos].symbol = '/';

  return 0;
}
