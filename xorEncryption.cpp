#include "xorEncryption.h"
#include <fstream>
#include <iostream>

using namespace std;

void xorEncyption::init() {
  this->inputFileString = this->openFile(this->inputFile);
  this->keyFileString = this->openFile(this->keyFile);
  xorEncyption::writeFile(this->inputFileString, this->outputFile);
  return;
}

string xorEncyption::openFile(string fileName) {
  ifstream file(fileName);
  string content((istreambuf_iterator<char>(file)),
                 (istreambuf_iterator<char>()));
  file.close();
  return content;
}

void xorEncyption::writeFile(string fileContents, string outputFile) {
  ofstream file(outputFile);
  if (!file.is_open()) {
    throw invalid_argument("Could not Write Output File!\n");
  }

  file << fileContents;
  file.close();
  return;
}

void xorEncyption::addBuffer(string fileContents) { return; }

void xorEncyption::removeBuffer(string fileContents) { return; }

void xorEncyption::encrypt(string fileContents, string keyFileString) {
  return;
}

void xorEncyption::decrypt(string fileContents, string keyFileString) {
  return;
}
