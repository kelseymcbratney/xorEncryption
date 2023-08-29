#include <complex>
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

  void init();

private:
  string openFile(string fileName);
  string addBuffer(string fileContent, int remainingBits);
  string removeBuffer(string fileContent);
  string encryptBlockCipher(string fileContent);
  string decryptBlockCipher(string fileContent);
  void writeFile(string fileContent, string outputFile);
  string streamCipher(string fileContent);
  string blockCipher(string fileContent);
  string inputFileString;
  string keyFileString;
  string blockCipherString;
  string streamCipherString;
};
