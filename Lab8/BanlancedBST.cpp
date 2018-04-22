//
// Created by Mieszko Wawrzyniak on 22/04/2018.
//

#include "BalancedBST.h"

void BalancedBST::Add(string word) {
  ++tree[word];
}

string BalancedBST::MostPopular() {
  string topStr;
  uint64_t topAmount = 0;
  
  for (const auto& obj: tree) {
    if (obj.second > topAmount) {
      topStr = obj.first;
      topAmount = obj.second;
    }
  }
  
  return topStr;
}