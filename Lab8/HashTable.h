//
// Created by Mieszko Wawrzyniak on 22/04/2018.
//

#ifndef LAB8_HASHTABLE_H
#define LAB8_HASHTABLE_H

#include <string>
#include <unordered_map>
#include "Counter.h"

using namespace std;

class HashTable: public Counter {
  unordered_map<string, uint64_t> map;

public:
  void Add(string word) override;
  void MostPopular() override;
};


#endif //LAB8_HASHTABLE_H
