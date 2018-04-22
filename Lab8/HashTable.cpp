//
// Created by Mieszko Wawrzyniak on 22/04/2018.
//

#include <string>
#include "HashTable.h"

using namespace std;

void HashTable::Add(string word) {
  ++map[word];
}

string HashTable::MostPopular() {
  string topStr;
  uint64_t topAmount = 0;
  
  for (const auto& obj: map) {
    if (obj.second > topAmount) {
      topStr = obj.first;
      topAmount = obj.second;
    }
  }
  
  return topStr;
}
