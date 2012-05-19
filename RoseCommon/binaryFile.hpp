#ifndef BINARYFILE_H
#define BINARYFILE_H

#include <fstream>
#include <iostream>
#include "typedef.h"
using namespace std;

class binaryFile {
  public:
    binaryFile():open(false) {}

    binaryFile(string file, bool write = false, DWORD b = 10240):open(false) {
      Open(file, write, b);
    }

    ~binaryFile() {
      Close();
    }


    bool Open(string file, bool w = false, DWORD b = 10240) {
      write = w;
      bufferSize = b;
      buffer = new char[bufferSize];
      fileReadLoc = 0;
      bufferReadLoc = 0;
      fileEnd = 0;

      string mode = "rb";
      if (write) mode = "wb";
      fh = fopen(file.c_str(), mode.c_str());
      open = (fh != NULL);
      checkBuffer();
      return open;
    }

    void Close() {
      if (open)
        fclose(fh);
      if (buffer != 0) {
        delete [] buffer;
        buffer = 0;
      }
      fileReadLoc = 0;
      bufferReadLoc = 0;
      fileEnd = 0;
    }


    // Read Functions
    template <class T> T Read(BYTE X = 0) {
      if (!checkBuffer(sizeof(T))) throw BFBUFFERERROR;
      T var;
      memcpy(&var, &buffer[bufferReadLoc - fileReadLoc], sizeof(T));
      bufferReadLoc += sizeof(T);
      if (X == 0) return var;
      for (DWORD i = 0; i < sizeof(T); i++)
        *(reinterpret_cast<char*>(&var) + i) ^= X;
      return var;
    }

    string String(DWORD len, BYTE X = 0) {
      if (!checkBuffer(len)) throw BFBUFFERERROR;
      if (len <= 0) return "";
      char var[len+1];
      memcpy(&var, &buffer[bufferReadLoc - fileReadLoc], len);
      bufferReadLoc += len;
      var[len] = 0;
      if (X == 0) return string(var);
      for (DWORD i = 0; i < len; i++)
        var[i] ^= (X);
      return string(var);
    }

    char* uBytes(DWORD len, BYTE X = 0) {
      char* var = new char[len];
      fseek(fh, bufferReadLoc, SEEK_SET);
      fread(var, len, 1, fh);
      if (!checkBuffer(len)) throw BFBUFFERERROR;
      bufferReadLoc += len;
      if (X == 0) return var;
      for (DWORD i = 0; i < len; i++)
        var[i] ^= (X);
      return var;
    }

    // Write Functions
    template <class T> void Write(T data, BYTE X = 0) {
      if (!write) return;
      if (X != 0)
        for (DWORD i = 0; i < sizeof(T); i++)
          *(reinterpret_cast<char*>(&data) + i) ^= X;
      fwrite(&data, sizeof(T), 1, fh);
    }
    void WriteS(char buf[], DWORD len, BYTE X = 0) {
      char data[len];
      memcpy(data, buf, len);
      if (!write) return;
      if (X != 0)
        for (DWORD i = 0; i < len; i++)
          data[i] ^= X;

        fwrite(data, len, 1, fh);
    }

    // Generic
    void seek(long int offset, int origin = SEEK_SET) {
      if (!open || write) return;
      switch (origin) {
        case SEEK_SET:
          if (offset < 1) return;
          if ((DWORD)offset > fileReadLoc && (DWORD)offset < (fileReadLoc + bufferSize)) {
            bufferReadLoc = offset;
            return;
          }
          bufferReadLoc = offset;
          if (!checkBuffer()) throw BFBUFFERERROR;
        break;
        case SEEK_CUR:
          bufferReadLoc += offset;
          if (!checkBuffer(offset)) throw BFBUFFERERROR;
        break;
      }
    }

    int tell() {
      if (write)
        return ftell(fh);
      else
        return bufferReadLoc;
    }

    enum BFERROR {ERROR_OPENING, BFBUFFERERROR};

  private:
    bool checkBuffer(int size = 0) {
      if (!open || (fileEnd != 0 && (bufferReadLoc + size) > fileEnd)) return false;
      if (size == 0 || (bufferReadLoc + size) > (fileReadLoc + bufferSize)) {
        fseek(fh, bufferReadLoc, SEEK_SET);
        if (feof(fh)) return false;
        fread(buffer, bufferSize, 1, fh);
        if (feof(fh)) fileEnd = ftell(fh);
        fileReadLoc = bufferReadLoc;
      }
      return true;
    }

    FILE *fh;
    bool write;
    bool open;

    // Buffered stuff
    DWORD bufferSize;
    char* buffer;
    DWORD fileReadLoc;
    DWORD bufferReadLoc;
    DWORD fileEnd;
};

#endif // BINARYFILE_H
