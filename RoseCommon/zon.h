#include "binaryFile.hpp"
#include "typedef.h"
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class ZON {
  public:
    ZON(string file);

    struct pointEntry {
      float x;
      float z;
      float y;
      string name;
    };

    DWORD getPointCount() {return Points.size();};
    ZON::pointEntry getPoint(string id);
    ZON::pointEntry getStart();
    ZON::pointEntry getRestore(DWORD id);
    DWORD getRestoreCount() {return Restore.size();};
    void printAll();

  private:
    DWORD blockCount;
    vector<DWORD> blockId;
    vector<DWORD> blockOffset;
    map<string, pointEntry> Points;
    vector<pointEntry> Restore;
    pointEntry Start;
};
