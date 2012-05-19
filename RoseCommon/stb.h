#include "binaryFile.hpp"
#include <iostream>
#include <vector>
using namespace std;

class STB {
  public:
    STB(string file);
    string getCell(int row, int col);
    int getRowCount() {return rowCount;};
    int getColCount() {return colCount;};

  private:
    vector< vector<string> > table;
    int rowCount;
    int colCount;
    string idColName;
    char formatKey[5];

};
