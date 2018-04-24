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

void UnsortedVector::MostPopular() {
  string topStr;
  uint64_t topAmount = 0;
  
  for (const _Elem& o: vec) {
  
    for (int i = 0; i < SIZE; ++i) {
      if (o.val <= arr[i].val) continue;
    
      for (int j = SIZE - 1; j > i; --j) {
        arr[j] = arr[j - 1];
      }
    
      arr[i].key = o.key;
      arr[i].val = o.val;
    
      break;
    }
  }
}

UnsortedVector::_Elem::_Elem(string key) {
  this->key = move(key);
  this->val = 1;
}
