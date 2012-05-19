#ifndef CON_H
#define CON_H

//#include "binaryFile.h"
#include "binaryFile.hpp"
#include <iostream>
#include <vector>
using namespace std;

class CON {
  public:
    struct entry;

    CON();
    ~CON();
    void LoadFile(string file);
    void WriteFile(string file);
    void New();
    CON::entry getEntry(DWORD dialogId, DWORD entryId);
    void setEntry(DWORD dialogId, DWORD entryId, entry Entry);
    DWORD getDialogCount();
    DWORD getEntryCount(DWORD dialogId);
    DWORD addEntry(DWORD d);
    DWORD deleteEntry(DWORD d, DWORD e);
    DWORD addDialog();
    bool writeLuc(string filename);
    bool loadLuc(string filename);
    DWORD getLucSize() {return lucLen;};
    string getFilename() {return filename;};
    bool IsOpen() {return Open;};

    // Data
    enum CONERROR {INVALID_DIALOGID, INVALID_ENTRYID, CONNOTOPEN};
    struct entry {
      DWORD entryId;
      DWORD command;
      DWORD data;
      char condFunc[0x20];
      char rewdFunc[0x20];
      DWORD strId;
    };

  private:
    struct dialog {
      DWORD size;
      DWORD entryCount;
      vector<entry> entries;
    };

    // Offsets and counts
    DWORD blockOffset; // What the hell's this?
    DWORD luaOffset;
    DWORD initCount;
    DWORD initOffset;
    DWORD dialogCount;
    DWORD dialogOffset;

    // Used in save calc
    const static DWORD entrysize = (sizeof(entry)+4);

    // Main data
    vector<entry> init;
    vector<dialog> dialogs;

    DWORD lucLen;
    char* luc;
    string filename;

    bool Open;

};


#endif // CON_H

