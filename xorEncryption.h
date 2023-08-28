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
  void addBuffer(string fileContent);
  void removeBuffer(string fileContent);
  void encrypt(string fileContent, string keyFileString);
  void decrypt(string fileContent, string keyFileString);
  void writeFile(string fileContent, string outputFile);
  string inputFileString;
  string keyFileString;
};
