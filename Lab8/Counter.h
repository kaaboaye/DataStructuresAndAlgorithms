//
// Created by Mieszko Wawrzyniak on 22/04/2018.
//

#ifndef LAB8_COUNTER_H
#define LAB8_COUNTER_H

#include <string>
#include <sstream>
#include "Element.h"

using namespace std;

class Counter {

protected:
  Node arr[SIZE];
  
public:
  virtual void Add(string word) = 0;
  virtual void MostPopular() = 0;
  void Load(istream &in);
  void Print();
};


#endif //LAB8_COUNTER_H
