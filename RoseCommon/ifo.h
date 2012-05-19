#include "binaryFile.hpp"
#include "typedef.h"
#include <iostream>
#include <vector>
using namespace std;

class IFO {
  public:
    IFO(string file);

    struct entry {
	    string strData;
			WORD unknown1;
			WORD eventId;
			DWORD objType;
			DWORD objId;
			DWORD mapPosX;
			DWORD mapPosY;
			float quatW;
			float quatX;
			float quatY;
			float quatZ;
			float posX;
			float posY;
			float posZ;
			float scaleX;
			float scaleY;
			float scaleZ;
    };

    struct NPC {
    	entry Entry;
    	DWORD unk1;
    	string conFile;
    };
    struct spawn {
    	string mobName;
    	DWORD mobId;
    	DWORD amount;
    };
    struct spawnGroup {
      entry Entry;
    	string spawnName;
    	DWORD basicMobCount;
    	vector<spawn> basicMobs;
    	DWORD tacMobCount;
    	vector<spawn> tacMobs;
    	DWORD interval;
    	DWORD limit;
    	DWORD range;
    	DWORD tacPoints;
    };
    struct TeleGate {
    	entry Entry;
    };

    // Accessor functions
    IFO::NPC getNPCEntry(DWORD id);
    IFO::spawnGroup getMobEntry(DWORD id);
    IFO::TeleGate getTeleEntry(DWORD id);

    DWORD getNPCCount() {return NPCList.size();};
    DWORD getMobCount() {return MobList.size();};
    DWORD getTeleCount() {return TeleGateList.size();};


  private:
    DWORD blockCount;
    vector<DWORD> blockType;
    vector<DWORD> blockOffset;
    vector<NPC> NPCList;
    vector<spawnGroup> MobList;
    vector<TeleGate> TeleGateList;
};
