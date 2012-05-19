#include "binaryFile.hpp"
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define STL_ENGLISH 1

class STL {
  public:
    STL(string file);

    struct language {
      string text;
      string comment;
      string quest1;
      string quest2;
      DWORD offset;
    };
    struct entry {
      DWORD id;
      string stringId;
      vector<language> lang;
    };

    int getEntryCount() {return entryCount;};
    int getLangCount() {return langCount;};
    string getType() {return type;};

    STL::entry getEntry(string id);
    void STL::printAll();

  private:
    map<string, entry> table;
    entry** index;
    string type;
    DWORD entryCount;
    DWORD langCount;

};
