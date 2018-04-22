//
// Created by Mieszko Wawrzyniak on 22/04/2018.
//

#ifndef LAB8_COUNTER_H
#define LAB8_COUNTER_H

#include <string>
#include <sstream>

using namespace std;

class Counter {
public:
  virtual void Add(string word) = 0;
  virtual string MostPopular() = 0;
  void Load(istream &in);
};


#endif //LAB8_COUNTER_H
