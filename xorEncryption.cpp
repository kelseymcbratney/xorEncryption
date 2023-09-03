#include "xorEncryption.h"
#include <algorithm>
#include <clocale>
#include <cwchar>
#include <fstream>
#include <iostream>

using namespace std;

void xorEncryption::init() {
  inputFileString = this->openFile(this->inputFile);
  keyFileString = this->openFile(this->keyFile);

  if (this->mode == "E") { // Encrypt

    if (this->cipherFunction == "S") { // Encrypt Stream Cipher

      string encryptedString = this->streamCipher(this->inputFileString);
      xorEncryption::writeFile(encryptedString, this->outputFile);

    } else if (this->cipherFunction == "B") { // Encrypt Block Cipher

      string bufferedString =
          this->calculateBufferRequired(this->inputFileString);
      string encryptedString =
          xorEncryption::encryptBlockCipher(bufferedString);
      xorEncryption::writeFile(encryptedString, this->outputFile);
    }

  } else if (this->mode == "D") { // Decrypt

    if (this->cipherFunction == "S") { // Decrypt Stream Cipher
      string decryptedString =
          xorEncryption::streamCipher(this->inputFileString);
      xorEncryption::writeFile(decryptedString, this->outputFile);

    } else if (this->cipherFunction == "B") { // Decrypt Block Cipher

      string buffedDecryptedString =
          xorEncryption::decryptBlockCipher(this->inputFileString);
      string decryptedString =
          xorEncryption::removeBuffer(buffedDecryptedString);
      xorEncryption::writeFile(decryptedString, this->outputFile);
    }
  }

  return;
}

string xorEncryption::openFile(string fileName) {
  ifstream file(fileName);
  string content((istreambuf_iterator<char>(file)),
                 (istreambuf_iterator<char>()));

  file.close();
  return content;
}

void xorEncryption::writeFile(string fileContents, string outputFile) {
  ofstream file(outputFile);
  if (!file.is_open()) {
    throw invalid_argument("Could not Write Output File!\n");
  }

  file << fileContents;
  file.close();
  return;
}

string xorEncryption::addBuffer(string fileContents, int remainingBits) {
  char paddingChar = '\x81';
  for (int i = 0; i < remainingBits; i++) {
    fileContents += paddingChar;
  }
  return fileContents;
}

string xorEncryption::removeBuffer(string fileContents) {
  char paddingChar = '\x81';
  while (!fileContents.empty() && fileContents.back() == paddingChar) {
    fileContents.pop_back();
  }
  return fileContents;
}

string xorEncryption::xorBlockCipher(string fileContents) {
  string xorString = "";
  int i = 0;

  for (char c : fileContents) {
    char key = this->keyFileString[i % this->keyFileString.length()];
    char xorResult = 0;

    for (int i = 7; i >= 0; --i) {
      bool fileBit = (c >> i) & 1;
      bool keyBit = (key >> i) & 1;
      bool xorBit = fileBit ^ keyBit;
      xorResult |= (xorBit << i);
    }

    xorString += xorResult;
    i++;
  }

  return xorString;
}

string xorEncryption::swapBlockCipher(string swapString) {
  int endIndex = 0;
  int frontIndex = swapString.length() - 1;
  bool isSwapped = 0;

  while (frontIndex <= endIndex) {
    char frontByte = swapString[frontIndex];
    char endByte = swapString[endIndex];

    if (frontByte == endByte) {
      break;
    }

    isSwapped = frontByte % 2;
    if (isSwapped) {
      swapString[endIndex] = frontByte;
      swapString[frontIndex] = endByte;
    }

    endIndex--;
    frontIndex++;
  }

  return swapString;
}

string xorEncryption::encryptBlockCipher(string fileContents) {
  string xorString = this->xorBlockCipher(fileContents);
  string encryptedString = this->swapBlockCipher(xorString);
  return encryptedString;
}

string xorEncryption::decryptBlockCipher(string encryptedString) {
  string swapString = this->swapBlockCipher(encryptedString);
  string decryptedString = this->xorBlockCipher(swapString);
  return decryptedString;
}

string xorEncryption::calculateBufferRequired(string fileContents) {
  int asciiBits = fileContents.length() * 8;
  int remainingBits = (128 - (asciiBits % 128)) % 128;
  string bufferedString = this->addBuffer(fileContents, remainingBits);
  return bufferedString;
}

string xorEncryption::streamCipher(string fileContents) {
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
