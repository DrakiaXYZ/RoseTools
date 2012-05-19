/***************************************************************
 * Name:      main.cpp
 * Author:    Steven "Drakia" Scott (Drakia@gmail.com)
 * Copyright: Steven "Drakia" Scott (www.thedgtl.net)
 * License:   GNU GPL v3 - Pretty much do whatever you want with it.
 **************************************************************/

#include "../RoseCommon/common.h"
#include "../RoseCommon/stb.h"
#include "../RoseCommon/zon.h"
using namespace std;

STB *mapStb;

int main()
{
  // Get the current working directory
  char buffer[_MAX_PATH];
  getcwd(buffer, _MAX_PATH);
  string folder = string(buffer);

  // Check that we're in a 3ddata folder. Scope so that vars are deleted afterwards.
  {
    unsigned int lastslash = folder.find_last_of("\\") + 1;
    string curfol = folder.substr(lastslash);
    if (strlower(curfol) != "3ddata") {
      cout << "::ERROR:: This program must be run from inside 3ddata" << endl;
      return 1;
    }
  }

  // Clear the list_respawnzones.sql file if it exists
  fclose(fopen("list_respawnzones.sql", "w"));

  // Load the STB's needed
  try {
    mapStb = NULL;
    mapStb = new STB("STB\\LIST_ZONE.STB");
  } catch (...) {
    if (mapStb != NULL) delete mapStb;
    cout << "Coultn't open STL/STB file" << endl;
    return 1;
  }

  // Parse ZON files from maplist
  DWORD mapCount = mapStb->getRowCount();
  FILE* file = fopen("list_respawnzones.sql", "a");
  for (unsigned int i = 1; i < mapCount; i++) {
    string name = mapStb->getCell(i, 2);
    if (name != "") {
      if (name.find_first_of("\\") >= name.length()) continue; // Invalid Map
      unsigned int firstslash = name.find_first_of("\\") + 1;
      string zonFile = name.substr(firstslash); // From just after the first \ to the end
      try {
        ZON zon(zonFile);
        DWORD restoreCount = zon.getRestoreCount();
        for (DWORD j = 0; j < restoreCount; j++) {
          ZON::pointEntry Entry = zon.getRestore(j);
          DWORD start = 0;
          if (Entry.name == "start") start = 1;
          fprintf(file, "INSERT INTO `list_respawnzones` VALUES (%d, %d, %.2f, %.2f, %d, %d);\n",
                        0, i, (Entry.x / 100 + 5200), (Entry.y / 100 + 5200), 10, start);
        }
      } catch (...) {
        cout << "Error opening zonFile: " << zonFile << endl;
        continue;
      }
    }
  }
  fclose(file);

  delete mapStb;
  return 0;
}
