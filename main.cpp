#include "xorEncryption.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  string arguementHelp = "Please Run Program with the Following Arguments\n"
                         "arg1 = Cipher Function -> 'B' or 'S'\n"
                         "arg2 = inputFile -> 'filename'\n"
                         "arg3 = outoutFile -> 'filename'\n"
                         "arg4 = keyFile -> 'filename'\n"
                         "arg5 = Encryption Mode -> 'E' or 'D'\n";

  string cipherFunction;
  string inputFile;
  string outputFile;
  string keyFile;
  string mode;

  try {
    if (argc != 6) {
      throw invalid_argument("Missing Arguments\n" + arguementHelp);
    }

    cipherFunction = argv[1];
    inputFile = argv[2];
    outputFile = argv[3];
    keyFile = argv[4];
    mode = argv[5];

    for (char &c : cipherFunction) {
      c = toupper(c);
    }

    for (char &c : mode) {
      c = toupper(c);
    }

    if (cipherFunction != "B" && cipherFunction != "S") {
      throw invalid_argument("Invalid Cipher Argument\n" + arguementHelp);
    }

    if (mode != "E" && mode != "D") {
      throw invalid_argument("Invalid Mode Argument\n" + arguementHelp);
    }

    ifstream file(inputFile);
    if (!file.good()) {
      file.close();
      throw invalid_argument("Input File Doesn't Exist\n" + arguementHelp);
    }
    file.close();

    ifstream file2(keyFile);
    if (!file2.good()) {
      file2.close();
      throw invalid_argument("Key File Doesn't Exist\n" + arguementHelp);
    } else {
      char c;
      while (file2.get(c)) {
        if (c == '\n') {
          file2.close();
          throw invalid_argument(
              "Key File Contains '\\n' Character, Remove it and Try Again\n" +
              arguementHelp);
        }
      }
    }

  } catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
    return -1;
  }

  xorEncryption Obj;

  Obj.cipherFunction = cipherFunction;
  Obj.inputFile = inputFile;
  Obj.outputFile = outputFile;
  Obj.keyFile = keyFile;
  Obj.mode = mode;

  Obj.init();

  return 0;
}
