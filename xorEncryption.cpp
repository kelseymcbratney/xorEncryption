#include "xorEncryption.h"
#include <algorithm>
#include <cwchar>
#include <fstream>
#include <iostream>

using namespace std;

void xorEncyption::init() {
  inputFileString = this->openFile(this->inputFile);
  keyFileString = this->openFile(this->keyFile);
  if (this->mode == "E") { // Encrypt

    if (this->cipherFunction == "S") { // Emcrypt Stream Cipher

      streamCipherString = this->streamCipher(this->inputFileString);
      xorEncyption::writeFile(this->streamCipherString, this->outputFile);

    } else if (this->cipherFunction == "B") { // Encrypt Block Cipher

      blockCipherString = this->blockCipher(this->inputFileString);
      xorEncyption::writeFile(this->blockCipherString, this->outputFile);
    }

  } else if (this->mode == "D") { // Decrypt

    if (this->cipherFunction == "S") { // Decrypt Stream Cipher
      string fileStreamContents =
          xorEncyption::streamCipher(this->inputFileString);
      xorEncyption::writeFile(fileStreamContents, this->outputFile);

    } else if (this->cipherFunction == "B") { // Decrypt Block Cipher

      string fileContents =
          xorEncyption::decryptBlockCipher(this->inputFileString);
      string fileBlockContents =
          xorEncyption::removeBuffer(this->inputFileString);
      xorEncyption::writeFile(fileBlockContents, this->outputFile);
    }
  }

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

string xorEncyption::addBuffer(string fileContents, int remainingBits) {
  char paddingChar = '\x81';
  for (int i = 0; i < remainingBits; i++) {
    fileContents += paddingChar;
  }
  return fileContents;
}

string xorEncyption::removeBuffer(string fileContents) {
  char paddingChar = '\x81';
  while (!fileContents.empty() && fileContents.back() == paddingChar) {
    fileContents.pop_back();
  }
  return fileContents;
}

string xorEncyption::encryptBlockCipher(string fileContents) {
  string encryptedString = "";
  return encryptedString;
}

string xorEncyption::decryptBlockCipher(string fileContents) {
  string encryptedString = "";
  return encryptedString;
}

string xorEncyption::blockCipher(string fileContents) {
  int asciiBits = fileContents.length() * 8;
  int remainingBits = (128 - (asciiBits % 128)) % 128;
  string bufferedBlockString = this->addBuffer(fileContents, remainingBits);
  string encryptedString = this->encryptBlockCipher(bufferedBlockString);
  return encryptedString;
}

string xorEncyption::streamCipher(string fileContents) {
  int i = 0;
  string encryptedString = "";

  for (char c : fileContents) {
    char key = this->keyFileString[i % this->keyFileString.length()];
    char xorResult = 0;

    for (int i = 7; i >= 0; --i) {
      bool fileBit = (c >> i) & 1;
      bool keyBit = (key >> i) & 1;
      bool xorBit = fileBit ^ keyBit;
      xorResult |= (xorBit << i);
    }

    encryptedString += xorResult;
    i++;
  }

  return encryptedString;
}
