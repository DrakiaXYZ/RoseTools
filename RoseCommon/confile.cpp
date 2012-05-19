#include "confile.h"

CON::CON() {
  Open = false;
  luc = 0;
}

void CON::LoadFile(string file) {
  // Clear out any existing data
  dialogs.clear();
  init.clear();
  if (luc != 0) {
    delete [] luc;
    luc = 0;
  }

  // Load new data
  binaryFile *fh;
  fh = new binaryFile();
  if (!fh->Open(file))
    return;

  filename = file;
  // Seek past unused data
  fh->seek(0x204);

  blockOffset = fh->Read<DWORD>();
  luaOffset = fh->Read<DWORD>();
  initCount = fh->Read<DWORD>();
  initOffset = fh->Read<DWORD>();
  dialogCount = fh->Read<DWORD>();
  dialogOffset = fh->Read<DWORD>();
  // Seek to the init block, skip over the lookup table
  fh->seek( (0x20C + initOffset) + (initCount * sizeof(DWORD)) );
  for (DWORD i = 0; i < initCount; i++) {
    entry Entry;
    Entry.entryId = fh->Read<DWORD>();
    Entry.command = fh->Read<DWORD>();
    Entry.data = fh->Read<DWORD>();
    strncpy(Entry.condFunc, fh->String(0x20).c_str(), 0x20);
    strncpy(Entry.rewdFunc, fh->String(0x20).c_str(), 0x20);
    Entry.strId = fh->Read<DWORD>();
    init.push_back(Entry);
  }

  // Seek to dialog block, skip over lookup table again
  fh->seek( (0x20C + dialogOffset) + (dialogCount * sizeof(DWORD)) );
  for (DWORD i = 0; i < dialogCount; i++) {
    dialog Dialog;
    Dialog.size = fh->Read<DWORD>();
    Dialog.entryCount = fh->Read<DWORD>();
    // The xor byte. This is going to be fun to implement
    BYTE X = (Dialog.entryCount % 2 == 0) ? Dialog.size : Dialog.entryCount;
    // Skip over lookup table, again, this is tedious
    fh->seek( (Dialog.entryCount * sizeof(DWORD)), SEEK_CUR );
    for (DWORD j = 0; j < Dialog.entryCount; j++) {
      entry Entry;
      Entry.entryId = fh->Read<DWORD>(X); // XOR
      Entry.command = fh->Read<DWORD>(X); // XOR
      Entry.data = fh->Read<DWORD>(X); // XOR
      strncpy(Entry.condFunc, fh->String(0x20, X).c_str(), 0x20); // XOR
      strncpy(Entry.rewdFunc, fh->String(0x20, X).c_str(), 0x20); // XOR
      Entry.strId = fh->Read<DWORD>(X); // XOR
      Dialog.entries.push_back(Entry);
    }
    dialogs.push_back(Dialog);
  }

  lucLen = fh->Read<DWORD>();
  BYTE X = (lucLen % 2) ? (lucLen & 0xFF) : ((luaOffset + 4 + lucLen) & 0xFF);
  luc = fh->uBytes(lucLen, X);
  Open = true;
  delete(fh);
}

void CON::New() {
  // Clear out any existing data
  dialogs.clear();
  init.clear();
  if (luc != 0) {
    delete [] luc;
    luc = 0;
    lucLen = 0;
  }
  filename = "";
  Open = true;

  // Offsets, wee
  blockOffset = 0x20C;
  luaOffset = 0;
  initCount = 1;
  initOffset = 0;
  dialogCount = 0;
  dialogOffset = 0;

  // Init Entry
  entry InitEntry;
  InitEntry.entryId = 0;
  InitEntry.command = 3;
  InitEntry.data = 0;
  memset(InitEntry.condFunc, '\0', 0x20);
  strncpy(InitEntry.condFunc, "TA_checkRepeat", 0x20);
  memset(InitEntry.rewdFunc, '\0', 0x20);
  InitEntry.strId = 3320;
  init.push_back(InitEntry);

  // First dialog, calls secondary dialog, hides menus and such
  DWORD DialogId = addDialog();

  entry Entry;
  // First entry, call TA_HideMenu
  Entry.entryId = 0;
  Entry.command = 2;
  Entry.data = 1;
  memset(Entry.condFunc, '\0', 0x20);
  strncpy(Entry.condFunc, "TA_hideMenu", 0x20);
  memset(Entry.rewdFunc, '\0', 0x20);
  Entry.strId = 3321;
  setEntry(DialogId, addEntry(DialogId), Entry);

  // Secondary dialog, closes windows and such
  DialogId = addDialog();
  for (DWORD i = 0; i < 7; i++) {
    Entry.entryId = i;
    Entry.command = 0;
    Entry.data = (DWORD)-1;
    memset(Entry.condFunc, '\0', 0x20);
    memset(Entry.rewdFunc, '\0', 0x20);
    Entry.strId = 3322 + i;
    setEntry(DialogId, addEntry(DialogId), Entry);
  }
}

void CON::WriteFile(string file) {
  if (!Open) return;
  // Random offset variable to be used throughout
  DWORD offset = 0;
  // Save the CON to file
  binaryFile *fh;
  try {
    fh = new binaryFile(file, true);
  } catch (...) {
    throw;
  }
  filename = file;
  // Pointless header thing
  for (int i = 0; i < 0x202; i++)
    fh->Write<BYTE>(0);
  fh->Write<WORD>(0xCCCC);

  DWORD blockOffset = 0x20C;

  // Block Offset
  fh->Write<DWORD>(blockOffset);
  // LUA Offset
  luaOffset = blockOffset + ((4 + initCount) * 4) + (initCount * sizeof(entry));
  for (DWORD i = 0; i < dialogCount; i++)
    luaOffset += dialogs.at(i).entryCount * entrysize + 8 + 4;
  fh->Write<DWORD>(luaOffset);
  // Init COunt, offset
  fh->Write<DWORD>(initCount);
  initOffset = fh->tell() + 12 - blockOffset; // 3 DWORDs, minus the offset
  fh->Write<DWORD>(initOffset);
  // Dialog Count, offset
  fh->Write<DWORD>(dialogCount);
  // 1 DWORD, init table, init blocks (entry), minus overall offset
  dialogOffset = fh->tell() + 4 + (initCount * entrysize) - blockOffset;
  fh->Write<DWORD>(dialogOffset);
  // init lookup table
  for (DWORD i = 0; i < initCount; i++) {
    fh->Write<DWORD>((i * sizeof(entry)) + (initCount * sizeof(DWORD))); // Offset from start of table to init blocks
  }

  // init table
  for (DWORD i = 0; i < initCount; i++) {
    fh->Write<DWORD>(i); // Entry ID
    fh->Write<DWORD>(init.at(i).command);
    fh->Write<DWORD>(init.at(i).data);
    fh->WriteS(init.at(i).condFunc, sizeof(init.at(i).condFunc));
    fh->WriteS(init.at(i).rewdFunc, sizeof(init.at(i).rewdFunc));
    fh->Write<DWORD>(init.at(i).strId);
  }

  // dialog lookup table
  offset = 0;
  for (DWORD i = 0; i < dialogCount; i++) {
    fh->Write<DWORD>((dialogCount * 4) + offset); // Offset from start of table
    offset += dialogs.at(i).entryCount * entrysize + 8;
  }

  // Dialog blocks
  for (DWORD i = 0; i < dialogCount; i++) {
    DWORD dialogSize = dialogs.at(i).entryCount * entrysize + 8;
    fh->Write<DWORD>(dialogSize);
    fh->Write<DWORD>(dialogs.at(i).entryCount);
    BYTE X = (dialogs.at(i).entryCount % 2 == 0) ? dialogSize : dialogs.at(i).entryCount;
    // dialog entry lookup table
    for (DWORD j = 0; j < dialogs.at(i).entryCount; j++)
      fh->Write<DWORD>((j * sizeof(entry)) + (dialogs.at(i).entryCount * sizeof(DWORD) + 8), X);
      // The +8 is because it's from the beginning of the dialog block, so include the size/entrycount
    for (DWORD j = 0; j < dialogs.at(i).entryCount; j++) {
      fh->Write<DWORD>(j, X); // Entry ID
      fh->Write<DWORD>(dialogs.at(i).entries.at(j).command, X);
      fh->Write<DWORD>(dialogs.at(i).entries.at(j).data, X);
      fh->WriteS(dialogs.at(i).entries.at(j).condFunc, sizeof(dialogs.at(i).entries.at(j).condFunc), X);
      fh->WriteS(dialogs.at(i).entries.at(j).rewdFunc, sizeof(dialogs.at(i).entries.at(j).rewdFunc), X);
      fh->Write<DWORD>(dialogs.at(i).entries.at(j).strId, X);
    }
  }

  // LUC block
  fh->Write<DWORD>(lucLen);
  BYTE X = (lucLen % 2) ? (lucLen & 0xFF) : ((luaOffset + 4 + lucLen) & 0xFF);
  fh->WriteS(luc, lucLen, X);

  fh->Close();
  delete fh;
}

CON::~CON() {
  if (luc != 0)
    delete [] luc;
}

CON::entry CON::getEntry(DWORD dialogId, DWORD entryId) {
  if (!Open) throw CONNOTOPEN;
  if (dialogId > dialogCount) throw INVALID_DIALOGID;
  if (entryId > dialogs.at(dialogId).entryCount) throw INVALID_ENTRYID;
  return dialogs.at(dialogId).entries.at(entryId);
}

void CON::setEntry(DWORD dialogId, DWORD entryId, entry Entry) {
  if (!Open) throw CONNOTOPEN;
  if (dialogId > dialogCount) throw INVALID_DIALOGID;
  if (entryId > dialogs.at(dialogId).entryCount) throw INVALID_ENTRYID;
  entry* e = &dialogs.at(dialogId).entries.at(entryId);
  e->entryId = Entry.entryId;
  e->command = Entry.command;
  e->data = Entry.data;
  memcpy(e->condFunc, Entry.condFunc, 0x20);
  memcpy(e->rewdFunc, Entry.rewdFunc, 0x20);
  e->strId = Entry.strId;
}

DWORD CON::getEntryCount(DWORD dialogId) {
  if (!Open) return 0;
  if (dialogId >= dialogCount) throw INVALID_DIALOGID;
  return dialogs.at(dialogId).entryCount;
}

DWORD CON::getDialogCount() {
  if (!Open) return 0;
  return dialogCount;
}

DWORD CON::addEntry(DWORD d) {
  if (!Open) throw CONNOTOPEN;
  entry e;
  e.entryId = dialogs.at(d).entryCount;
  e.command = 0;
  e.data = 0;
  memset(e.condFunc, '\0', 0x20);
  memset(e.rewdFunc, '\0', 0x20);
  e.strId = 0;
  dialogs.at(d).entries.push_back(e);
  dialogs.at(d).entryCount++;
  dialogs.at(d).size += 84; // Size of an entry
  return dialogs.at(d).entryCount-1;
}

DWORD CON::deleteEntry(DWORD d, DWORD e) {
  if (!Open) throw CONNOTOPEN;
  dialogs.at(d).entries.erase(dialogs.at(d).entries.begin() + e);
  dialogs.at(d).entryCount--;
  dialogs.at(d).size -= 84;
  if (e >= dialogs.at(d).entryCount) e--;
  return e;
}

DWORD CON::addDialog() {
  if (!Open) throw CONNOTOPEN;
  dialog d;
  d.size = 8;
  d.entryCount = 0;
  dialogs.push_back(d);
  dialogCount++;
  return dialogCount - 1;
}

bool CON::writeLuc(string filename) {
    if (!Open) throw CONNOTOPEN;
    ofstream fh(filename.c_str(), ios_base::out | ios_base::binary);
    if (!fh.good()) return false;
    fh.write(luc, lucLen);
    fh.close();
    return true;
}

bool CON::loadLuc(string filename) {
    if (!Open) throw CONNOTOPEN;
    if (luc != 0) {
      delete [] luc;
      luc = 0;
    }
    ifstream fh(filename.c_str(), ios_base::in | ios_base::binary);
    if (!fh.good()) return false;
    fh.seekg(0, ios_base::end);
    DWORD size = fh.tellg();
    fh.seekg(0, ios_base::beg);
    luc = new char[size];
    fh.read(luc, size);
    lucLen = size;
    return true;
}



