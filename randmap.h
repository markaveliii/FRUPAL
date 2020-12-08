#include "library.h"
#include "maploader.h"
#include <stdlib.h>
#include <time.h>

#define PATH 100
#define SWAMPS 15
#define OBS 50
#define FOODS 50
#define TOOLS 50
#define CHESTS 50
#define CLUES 5
#define BINO 50

using namespace std;

int mapRandom(cell island[128][128], obstacle obsList[100], food foodList[100], tool toolList[100], treasure chestList[100], hero& player);
