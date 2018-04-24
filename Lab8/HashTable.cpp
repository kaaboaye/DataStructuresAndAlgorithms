//
// Created by Mieszko Wawrzyniak on 22/04/2018.
//

#include <string>
#include "HashTable.h"

using namespace std;

void HashTable::Add(string word) {
  ++map[word];
}

void HashTable::MostPopular() {
  
  for (const auto& o: map) {
  
    for (int i = 0; i < SIZE; ++i) {
      if (o.second <= arr[i].val) continue;
      
      for (int j = SIZE - 1; j > i; --j) {
        arr[j] = arr[j - 1];
      }
      
      arr[i].key = o.first;
      arr[i].val = o.second;
  
      break;
    }
    
  }
}
