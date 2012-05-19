#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <fstream>
#include <dirent.h>
#include <vector>
#include <cmath>
#include <sstream>
#include "typedef.h"

using namespace std;

string addslashes(string str);

float NpcQuaterToRot(float qw, float qx, float qy, float qz);

string strlower(string str);

void writeLog(string file, char* line);

#endif // COMMON_H

