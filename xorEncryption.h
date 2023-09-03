#include <complex>
#include <iostream>
using namespace std;
#pragma once

class xorEncryption {

public:
  string cipherFunction;
  string inputFile;
  string outputFile;
  string keyFile;
  string mode;
  void init();

private:
  string inputFileString;
  string keyFileString;
  string openFile(string fileName);
  string addBuffer(string fileContent, int remainingBits);
  string removeBuffer(string fileContent);
  string encryptBlockCipher(string fileContent);
  string decryptBlockCipher(string fileContent);
  void writeFile(string fileContent, string outputFile);
  string streamCipher(string fileContent);
  string calculateBufferRequired(string fileContent);
  string swapBlockCipher(string fileContents);
  string xorBlockCipher(string fileContents);
};
