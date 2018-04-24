//
// Created by Mieszko Wawrzyniak on 22/04/2018.
//

#ifndef LAB8_UNSORTEDVECTOR_H
#define LAB8_UNSORTEDVECTOR_H

#include <vector>
#include "Counter.h"

using namespace std;

class UnsortedVector: public Counter {
  struct _Elem {
    string key;
    uint64_t val;
  
    explicit _Elem(string key);
  };
  
  vector<_Elem> vec;

public:
  void Add(string word) override;
  void MostPopular() override;
};


#endif //LAB8_UNSORTEDVECTOR_H
