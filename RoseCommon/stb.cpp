#include "stb.h"

STB::STB(string file) {
  binaryFile *fh;
  try {
    fh = new binaryFile(file);
  } catch (...) {
    cout << "Can't open file" << endl;
    throw;
  }

  // formatKey, null terminate
  formatKey[0] = fh->Read<BYTE>();
  formatKey[1] = fh->Read<BYTE>();
  formatKey[2] = fh->Read<BYTE>();
  formatKey[3] = fh->Read<BYTE>();
  formatKey[4] = 0;

  // Offsets, counts
  /*int dataOffset = */fh->Read<DWORD>();
  rowCount = fh->Read<DWORD>() - 1;
  colCount = fh->Read<DWORD>();

  // Unknown
  fh->Read<DWORD>();

  // Column Widths
  for (int i = 0; i < colCount + 1; i++)
    fh->Read<WORD>();

  // Column Titles
  for (int i = 0; i < colCount; i++)
    fh->seek(fh->Read<WORD>(), SEEK_CUR);

  // id Column Name
  fh->seek(fh->Read<WORD>(), SEEK_CUR);

  // Get first column
  for (int i = 0; i < rowCount; i++) {
    vector<string> tmp;
    tmp.push_back(fh->String(fh->Read<WORD>()));
    table.push_back(tmp);
  }

  // Populate table
  for (int i = 0; i < rowCount; i++)
    for (int j = 1; j < colCount; j++)
      table.at(i).push_back(fh->String(fh->Read<WORD>()));

  delete(fh);

}

string STB::getCell(int row, int col) {
  if (row < 0 || (DWORD)row >= table.size()) throw -1;
  if (col < 0 || (DWORD)col >= table.at(row).size()) throw -2;
  return table[row][col];
}
