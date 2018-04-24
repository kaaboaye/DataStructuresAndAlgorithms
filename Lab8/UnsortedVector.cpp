//
// Created by Mieszko Wawrzyniak on 22/04/2018.
//

#include <string>
#include "UnsortedVector.h"

using namespace std;

void UnsortedVector::Add(string word) {
  for (_Elem &elem : vec) {
    if (elem.key == word) {
      ++elem.val;
      return;
    }
  }
  
  _Elem elem(word);
  vec.push_back(elem);
}

string UnsortedVector::MostPopular() {
  string topStr;
  uint64_t topAmount = 0;
  
  for (const _Elem& obj: vec) {
    if (obj.val > topAmount) {
      topStr = obj.key;
      topAmount = obj.val;
    }
  }
  
  return topStr;
}

UnsortedVector::_Elem::_Elem(string key) {
  this->key = move(key);
  this->val = 1;
}
