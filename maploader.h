#include "library.h"
#include <stdlib.h>
#include <time.h>

static int objLocation[2][128*128];

int mapExport(const char* map, cell island[128][128]);
int mapImport(const char* map, cell island[128][128]);
