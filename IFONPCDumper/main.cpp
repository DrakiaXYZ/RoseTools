/***************************************************************
 * Name:      main.cpp
 * Author:    Steven "Drakia" Scott (Drakia@gmail.com)
 * Copyright: Steven "Drakia" Scott (www.thedgtl.net)
 * License:   GNU GPL v3 - Pretty much do whatever you want with it.
 **************************************************************/

#include "../RoseCommon/common.h"
#include "../RoseCommon/stb.h"
#include "../RoseCommon/stl.h"
#include "../RoseCommon/ifo.h"
#include "../RoseCommon/zon.h"

using namespace std;

void parseMap(string mapFolder, string mapName, int mapId);

STB *mapStb;
STB *npcStb;
STL *npcStl;
STB *warpStb;

int main(int argc, char *argv[]) {
  // Get the current working directory
  char buffer[_MAX_PATH];
  getcwd(buffer, _MAX_PATH);
  string folder = string(buffer);

  // Check that we're in a 3ddata folder. Scope so that vars are deleted afterwards.
  {
    unsigned int lastslash = folder.find_last_of("\\") + 1;
    string curfol = folder.substr(lastslash);
    cout << strlower(curfol) << endl;
    if (strlower(curfol) != "3ddata") {
      cout << "::ERROR:: This program must be run from inside 3ddata" << endl;
      return 1;
    }
  }

  // Clear the list_mobgroups file if it exists
  fclose(fopen("list_mobgroups.sql", "w"));
  // Clear the list_npcs.sql file if it exists
  fclose(fopen("list_npcs.sql", "w"));
  // Clear the list_telegates.sql file if it exists
  fclose(fopen("list_telegates.sql", "w"));


  // Load the STB's needed
  try {
    mapStb = NULL;
    npcStb = NULL;
    npcStl = NULL;
    warpStb = NULL;
    mapStb = new STB("STB\\LIST_ZONE.STB");
    npcStb = new STB("STB\\LIST_NPC.STB");
    npcStl = new STL("STB\\LIST_NPC_S.STL");
    warpStb = new STB("STB\\WARP.STB");
  } catch (...) {
    if (mapStb != NULL) delete mapStb;
    if (npcStb != NULL) delete npcStb;
    if (npcStl != NULL) delete npcStl;
    if (warpStb != NULL) delete warpStb;
    cout << "Coultn't open STL/STB file" << endl;
    return 1;
  }

  // Loop through the mapList and load IFO's for all the listed maps
  DWORD mapCount = mapStb->getRowCount();
  for (unsigned int i = 1; i < mapCount; i++) {
    string name = mapStb->getCell(i, 2);
    if (name != "") {
      unsigned int lastslash = name.find_last_of("\\");
      if (lastslash >= name.length()) continue; // No slashes, so it's not a valid path
      name = name.substr(0, lastslash); // Cut off the filename
      lastslash = name.find_last_of("\\") + 1;
      unsigned int firstslash = name.find_first_of("\\") + 1;
      string folder = name.substr(firstslash); // From just after the first \ to the end
      name = name.substr(lastslash); // Just the map folder name
      parseMap(folder, name, i);
    }
  }

  // Free used resources
  delete mapStb;
  delete npcStb;
  delete npcStl;
  delete warpStb;
  return 0;
}

void parseMap(string mapFolder, string mapName, int mapId) {
  // Create a handle to map directory
  DIR *mapDir = opendir(mapFolder.c_str());
  if (mapDir == NULL) {
    cout << "Could not open mapDir " << mapFolder << endl;
    return;
  }

  //static int mobGroupId = 1;
  struct dirent *mapFile;
  // Keep count of mobs/NPCs
  unsigned int NPCCount = 0;
  unsigned int MobCount = 0;
  unsigned int TeleCount = 0;

  // Output what map we're working on
  cout << "Map: " << mapId << " -- " << mapName << endl;

  // Scan through the map folder for IFO files
  while ((mapFile = readdir(mapDir)) != NULL) {

    string mapFileName = string(mapFile->d_name);
    // If the maps filenme is less than 4 letters, we have no extension
    if (mapFileName.length() < 4) continue;
    // If the extension isn't IFO then we don't want to use it
    if (mapFileName.substr(mapFileName.length() - 3) != "IFO") continue;

    // Open the IFO file for reading
    IFO ifo((mapFolder + "/" + mapFileName).c_str());

    // Parse NPCs
    DWORD npcCount = ifo.getNPCCount();
    for (DWORD i = 0; i < npcCount; i++) {
      FILE* file = fopen("list_npcs.sql", "a");
      IFO::NPC npc = ifo.getNPCEntry(i);
      string stlId = npcStb->getCell(npc.Entry.objId, 41);
      if (stlId.length() == 0) continue;
      string npcName = npcStl->getEntry(stlId).lang.at(STL_ENGLISH).text;
      if (npcName == "") npcName = "[NoNameNPC]";
      NPCCount++;
      fprintf(file, "INSERT INTO `list_npcs` VALUES (%d, '%s', %d, %d, %.3f, %.2f, %.2f);\n",
                    0, addslashes(npcName).c_str(), npc.Entry.objId, mapId,
                    (NpcQuaterToRot(npc.Entry.quatW, npc.Entry.quatX, npc.Entry.quatY, npc.Entry.quatZ)),
                    (5200 + (npc.Entry.posX / 100.0)), (5200 + (npc.Entry.posY / 100.0)));
      fclose(file);
    }

    // Parse Mobs
    DWORD mobCount = ifo.getMobCount();
    for (DWORD i = 0; i < mobCount; i++) {
      FILE* file = fopen("list_mobgroups.sql", "a");
      IFO::spawnGroup mob = ifo.getMobEntry(i);

      // Create a string stream for the mob list.
      // List is mobId,amount,tac|
      stringstream mobList;
      for (DWORD j = 0; j < mob.basicMobCount; j++) {
        if (j != 0)
          mobList << "|";
        mobList << mob.basicMobs.at(j).mobId << "," << mob.basicMobs.at(j).amount << ",0";
      }
      if (mob.basicMobCount != 0 && mob.tacMobCount != 0)
        mobList << "|";
      for (DWORD j = 0; j < mob.tacMobCount; j++) {
        if (j != 0)
          mobList << "|";
        mobList << mob.tacMobs.at(j).mobId << "," << mob.tacMobs.at(j).amount << ",1";
      }
      MobCount++;
      fprintf(file, "INSERT INTO `list_mobgroups` VALUES (%d, %d, %.2f, %.2f, %d, %d, %d, %d, '%s');\n",
                    0, mapId, ((mob.Entry.posX / 100.0) + 5200), ((mob.Entry.posY / 100.0) + 5200),
                    mob.range, mob.interval, mob.limit, mob.tacPoints, mobList.str().c_str());
      fclose(file);
    }

    // Parse TeleGates
    DWORD teleCount = 0;
    teleCount = ifo.getTeleCount();
    for (DWORD i = 0; i < teleCount; i++) {
      IFO::TeleGate tele = ifo.getTeleEntry(i);
      DWORD destMap = atoi(warpStb->getCell(tele.Entry.unknown1, 2).c_str());

      string destMapFile = mapStb->getCell(destMap, 2);
      DWORD firstslash = destMapFile.find_first_of("\\") + 1;
      if (firstslash >= destMapFile.length()) continue; // Invalid dest map
      destMapFile = destMapFile.substr(firstslash);
      float destX = 0;
      float destY = 0;
      float srcX = tele.Entry.posX / 100 + 5200;
      float srcY = tele.Entry.posY / 100 + 5200;
      try {
        ZON zon((destMapFile).c_str());
        string teleId = warpStb->getCell(tele.Entry.unknown1, 3);
        ZON::pointEntry point = zon.getPoint(teleId);
        destX = point.x / 100 + 5200;
        destY = point.y / 100 + 5200;
      } catch (...) {
        cout << "Invalid telegate destination. Telegate: " << tele.Entry.unknown1 << endl;
        continue;
      }
      TeleCount++;
      // Format: id, srcmap, srcx, srcy, destmap, destx, desty.
      FILE* file = fopen("list_telegates.sql", "a");
      fprintf(file, "INSERT INTO `list_telegates` VALUES (%d, %d, %.2f, %.2f, %d, %.2f, %.2f);\n",
                    tele.Entry.unknown1, mapId, srcX, srcY, destMap, destX, destY);
      fclose(file);
    }
  }
  cout << "-- NPCs: " << NPCCount << endl;
  cout << "-- Mobs: " << MobCount << endl;
  cout << "-- Telegates: " << TeleCount << endl;
  closedir(mapDir);
}

