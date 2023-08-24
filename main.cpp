#include "xorEncyption.h"
#include <cctype>
#include <cstring>
#include <iostream>
#include <stdexcept>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 6) {
    throw invalid_argument("Missing Arguments");
  }

  string cipherFunction = argv[1];
  string inputFile = argv[2];
  string outputFile = argv[3];
  string keyFile = argv[4];
  string mode = argv[5];

  if (cipherFunction != "B" && cipherFunction != "G") {
    throw invalid_argument("Invalid Cipher Argument");
  }

  if (mode != "E" && mode != "D") {
    throw invalid_argument("Invalid Mode Argument");
  }

  xorEncyption Obj;

  Obj.cipherFunction = cipherFunction;
  Obj.inputFile = inputFile;
  Obj.outputFile = outputFile;
  Obj.keyFile = keyFile;
  Obj.mode = mode;

  return 0;
}
