#include "library.h"
#include <cstring>

using namespace std;

int mapExport(const char* map, cell island[128][128], obstacle obsList[100], food foodList[100], tool toolList[100], treasure chestList[100], hero& player);
int mapImport(const char* map, cell island[128][128], obstacle obsList[100], food foodList[100], tool toolList[100], treasure chestList[100]);
