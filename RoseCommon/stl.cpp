#include "stl.h"

STL::STL(string file) {
  binaryFile *fh;
  try {
    fh = new binaryFile(file);
  } catch (...) {
    throw;
  }

  // formatKey, null terminate
  type = fh->String(fh->Read<BYTE>());

  // Use an index to bypass map sorting problem
  entryCount = fh->Read<DWORD>();
  index = new entry*[entryCount];
  for (DWORD i = 0; i < entryCount; i++) {
    entry item;
    item.stringId = fh->String(fh->Read<BYTE>());
    item.id = fh->Read<DWORD>();
    table[item.stringId] = item;
    index[i] = &table[item.stringId];
  }

  vector<DWORD> langOffset;
  langCount = fh->Read<DWORD>();
  for (DWORD i = 0; i < langCount; i++) {
    langOffset.push_back(fh->Read<DWORD>());
  }

  for (DWORD i = 0; i < langCount; i++) {
    fh->seek(langOffset.at(i));
    for (DWORD j = 0; j < entryCount; j++) {
      entry* Entry = index[j];
      language lang;
      lang.offset = fh->Read<DWORD>();
      Entry->lang.push_back(lang);
    }
  }

  for (DWORD i = 0; i < langCount; i++) {
    for (DWORD j = 0; j < entryCount; j++) {
      entry* Entry = index[j];
      language *item = &Entry->lang.at(i);
      fh->seek(item->offset);
      item->text = fh->String(fh->Read<BYTE>());
      item->comment = "";
      item->quest1 = "";
      item->quest2 = "";
      if (type == "QEST01" || type == "ITST01") {
        item->comment = fh->String(fh->Read<BYTE>());
        if (type == "QEST01") {
          item->quest1 = fh->String(fh->Read<BYTE>());
          item->quest2 = fh->String(fh->Read<BYTE>());
        }
      }
    }
  }

  delete(fh);

}

STL::entry STL::getEntry(string id) {
  map<string, entry>::iterator iter = table.find(id);
  if (iter == table.end()) throw -1;
  return iter->second;
}

void STL::printAll() {
  for (map<string, entry>::iterator iter = table.begin(); iter != table.end(); iter++) {
    entry E = iter->second;
    cout << "Text: " << E.lang.at(1).text << endl;
  }
}

