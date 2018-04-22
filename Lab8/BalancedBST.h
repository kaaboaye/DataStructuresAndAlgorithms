//
// Created by Mieszko Wawrzyniak on 22/04/2018.
//

#ifndef LAB8_BALANCEDBST_H
#define LAB8_BALANCEDBST_H


#include "Counter.h"
#include <map>
#include <string>

using namespace std;

class BalancedBST: public Counter {
  map<string, uint64_t> tree;

public:
  void Add(string word) override;
  string MostPopular() override;
};


#endif //LAB8_BALANCEDBST_H
