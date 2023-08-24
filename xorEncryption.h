#include <iostream>
using namespace std;
#pragma once

class xorEncyption {
public:
  string cipherFunction;
  string inputFile;
  string outputFile;
  string keyFile;
  string mode;

  void openFile();
};
