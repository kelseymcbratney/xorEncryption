#include "xorEncryption.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  string arguementHelp = "Please Run Program with the Following Arguments\n"
                         "arg1 = cipherFunction -> 'B' or 'S'\n"
                         "arg2 = inputFile -> 'filename'\n"
                         "arg3 = outoutFile -> 'filename'\n"
                         "arg4 = keyFile -> 'filename'\n"
                         "arg5 = mode -> 'E' or 'D'\n";

  if (argc != 6) {
    throw invalid_argument("Missing Arguments\n" + arguementHelp);
  }

  string cipherFunction = argv[1];
  string inputFile = argv[2];
  string outputFile = argv[3];
  string keyFile = argv[4];
  string mode = argv[5];

  for (char c : cipherFunction) {
    cipherFunction = +std::toupper(c);
  }

  for (char c : mode) {
    mode = +std::toupper(c);
  }

  if (cipherFunction != "B" && cipherFunction != "S") {
    throw invalid_argument("Invalid Cipher Argument\n" + arguementHelp);
  }

  if (mode != "E" && mode != "D") {
    throw invalid_argument("Invalid Mode Argument\n" + arguementHelp);
  }

  ifstream file(inputFile);
  if (file.good() == false) {
    file.close();
    throw invalid_argument("Input File Doesn't Exist\n" + arguementHelp);
  }
  file.close();

  ifstream file2(keyFile);
  if (file2.good() == false) {
    file2.close();
    throw invalid_argument("Key File File Doesn't Exist\n" + arguementHelp);
  } else {
    char c;
    while (file2.get(c)) {
      if (c == '\n') {
        throw invalid_argument(
            "Key File Contains '\\n' Character, Remove it and Try Again\n" +
            arguementHelp);
      }
    }
  }
  file2.close();

  xorEncyption Obj;

  Obj.cipherFunction = cipherFunction;
  Obj.inputFile = inputFile;
  Obj.outputFile = outputFile;
  Obj.keyFile = keyFile;
  Obj.mode = mode;

  Obj.init();

  return 0;
}
