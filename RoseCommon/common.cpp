#include "common.h"

float NpcQuaterToRot(float qw, float qx, float qy, float qz){
    float qw2 = qw*qw;
    float qx2 = qx*qx;
    float qy2 = qy*qy;
    float qz2 = qz*qz;
    float yaw = atan2(qw*qz + qx*qy, qy2-qx2-qz2+qw2);
    yaw = yaw * 180 / M_PI;
    if (yaw < 0) yaw += 360;
    return yaw;
}

string addslashes(string str) {
  unsigned int ind = 0;
  while (ind < str.length()) {
    ind = str.find("'", ind);
    if (ind < str.length()) {
      str.insert(ind, "'");
      ind+=2;
    }
  }
  return str;
}

string strlower(string str) {
  string ret;
  for (unsigned int i = 0; i < str.length(); i++) {
    char tmp = tolower(str[i]);
    ret.append( 1, tmp );
  }
  return ret;
}

void writeLog(string file, char* line) {
  FILE *fh = fopen(file.c_str(), "a");
  fputs(line, fh);
  fclose(fh);
}
