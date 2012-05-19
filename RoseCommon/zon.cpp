#include "zon.h"

ZON::ZON(string file) {
  binaryFile *fh;
  try {
    fh = new binaryFile(file);
  } catch (...) {
    throw;
  }

  // Offsets, types
  blockCount = fh->Read<DWORD>();
  for (DWORD i = 0; i < blockCount; i++) {
  	blockId.push_back(fh->Read<DWORD>());
  	blockOffset.push_back(fh->Read<DWORD>());
  }

  for (DWORD i = 0; i < blockCount; i++) {
    fh->seek(blockOffset.at(i));
    DWORD bId = blockId.at(i);
    if (bId != 1) continue;

    DWORD entryCount = fh->Read<DWORD>();
    for (DWORD j = 0; j < entryCount; j++) {
      pointEntry Entry;
      Entry.x = fh->Read<FLOAT>();
      Entry.z = fh->Read<FLOAT>();
      Entry.y = fh->Read<FLOAT>();
      Entry.name = fh->String(fh->Read<BYTE>());

      if (Entry.name == "restore" || Entry.name == "start") Restore.push_back(Entry);
      else Points[Entry.name] = Entry;
    }
  }

  delete(fh);
}

ZON::pointEntry ZON::getPoint(string id) {
  map<string, pointEntry>::iterator iter = Points.find(id);
  if (iter == Points.end()) throw -1;
  return iter->second;
}

ZON::pointEntry ZON::getStart() {
  return Start;
}

ZON::pointEntry ZON::getRestore(DWORD id) {
  if (id < 0 || id >= Restore.size()) throw -1;
  return Restore.at(id);
}

void ZON::printAll() {
  for (map<string, pointEntry>::iterator iter = Points.begin(); iter != Points.end(); iter++) {
    pointEntry point = iter->second;
    cout << "X: " << (point.x/100 + 5200) << " Y: " << (point.y/100 + 5200) << " Z: " << point.z << " Name: " << point.name << endl;
  }
}
