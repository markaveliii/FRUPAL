#include "library.h"
#include <cstring>

int mapExport(const char* map, cell island[128][128], obstacle obsList[100], food foodList[100], tool toolList[100], treasure chestList[100]);
int mapImport(const char* map, cell island[128][128], obstacle obsList[100], food foodList[100], tool toolList[100], treasure chestList[100]);
