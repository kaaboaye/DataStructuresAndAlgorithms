//
// Created by Mieszko Wawrzyniak on 22/04/2018.
//

#include <string>
#include <sstream>
#include <iostream>
#include "Counter.h"

using namespace std;

static bool getWord(istream &in, string &word) {
  word = "";
  char c;
  
  bool eof = in.eof();
  // Omit non word characters
  while (true) {
    if (in.eof()) {
      return false;
    }
    
    in >> noskipws >> c;
    
    if (isalpha(c)) {
      word = (char) tolower(c);
      break;
    }
  }
  
  // Load rest of the word
  while (true) {
    in >> noskipws >> c;
    if (in.eof() || !isalpha(c)) {
      break;
    }
    word += (char) tolower(c);
  }
  
  
  bool ret = word.empty();
  return !word.empty();
}

void Counter::Load(istream &in) {
  string word;
  
  while (getWord(in, word)) {
    Add(word);
  }
}

void Counter::Print() {
  for (int i = 0; i < SIZE; ++i) {
    cout << arr[i].key << " " << arr[i].val << endl;
  }
}
