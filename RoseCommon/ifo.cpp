#include "ifo.h"

IFO::IFO(string file) {
  binaryFile *fh;
  try {
    fh = new binaryFile(file);
  } catch (...) {
    throw;
  }

  // Offsets, types
  blockCount = fh->Read<DWORD>();
  for (DWORD i = 0; i < blockCount; i++) {
  	blockType.push_back(fh->Read<DWORD>());
  	blockOffset.push_back(fh->Read<DWORD>());
  }

  for (DWORD i = 0; i < blockCount; i++) {
    fh->seek(blockOffset.at(i));
    DWORD bType = blockType.at(i);
    if (bType != 2 && bType != 8 && bType != 10) continue;
    DWORD entryCount = fh->Read<DWORD>();

    for (DWORD j = 0; j < entryCount; j++) {
      entry Entry;
      Entry.strData = fh->String(fh->Read<BYTE>());
      Entry.unknown1 = fh->Read<WORD>();
      Entry.eventId = fh->Read<WORD>();
      Entry.objType = fh->Read<DWORD>();
      Entry.objId = fh->Read<DWORD>();
      Entry.mapPosX = fh->Read<DWORD>();
      Entry.mapPosY = fh->Read<DWORD>();
      Entry.quatX = fh->Read<FLOAT>();
      Entry.quatY = fh->Read<FLOAT>();
      Entry.quatZ = fh->Read<FLOAT>();
      Entry.quatW = fh->Read<FLOAT>();
      Entry.posX = fh->Read<FLOAT>();
      Entry.posY = fh->Read<FLOAT>();
      Entry.posZ = fh->Read<FLOAT>();
      Entry.scaleX = fh->Read<FLOAT>();
      Entry.scaleY = fh->Read<FLOAT>();
      Entry.scaleZ = fh->Read<FLOAT>();

      if (bType == 2) {
        NPC npc;
        npc.Entry = Entry;
        npc.unk1 = fh->Read<DWORD>();
        npc.conFile = fh->String(fh->Read<BYTE>());
        NPCList.push_back(npc);
      } else if (bType == 8) {
        spawnGroup sGroup;
        sGroup.Entry = Entry;
        sGroup.spawnName = fh->String(fh->Read<BYTE>());

        sGroup.basicMobCount = fh->Read<DWORD>();
        for (DWORD l = 0; l < sGroup.basicMobCount; l++) {
          spawn s;
          s.mobName = fh->String(fh->Read<BYTE>());
          s.mobId = fh->Read<DWORD>();
          s.amount = fh->Read<DWORD>();
          sGroup.basicMobs.push_back(s);
        }

        sGroup.tacMobCount = fh->Read<DWORD>();
        for (DWORD l = 0; l < sGroup.tacMobCount; l++) {
          spawn s;
          s.mobName = fh->String(fh->Read<BYTE>());
          s.mobId = fh->Read<DWORD>();
          s.amount = fh->Read<DWORD>();
          sGroup.tacMobs.push_back(s);
        }

        sGroup.interval = fh->Read<DWORD>();
        sGroup.limit = fh->Read<DWORD>();
        sGroup.range = fh->Read<DWORD>();
        sGroup.tacPoints = fh->Read<DWORD>();
        MobList.push_back(sGroup);
      } else if (bType == 10) {
        TeleGate tGate;
        tGate.Entry = Entry;
        TeleGateList.push_back(tGate);
      }
    }
  }

  delete(fh);
}

IFO::NPC IFO::getNPCEntry(DWORD id) {
  if (id < 0 || id >= NPCList.size()) throw -1;
  return NPCList.at(id);
}

IFO::spawnGroup IFO::getMobEntry(DWORD id) {
  if (id < 0 || id >= MobList.size()) throw -2;
  return MobList.at(id);
}

IFO::TeleGate IFO::getTeleEntry(DWORD id) {
  if (id < 0 || id >= TeleGateList.size()) throw -3;
  return TeleGateList.at(id);
}
