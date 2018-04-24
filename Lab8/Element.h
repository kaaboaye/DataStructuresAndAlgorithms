//
// Created by Mieszko Wawrzyniak on 22/04/2018.
//

#ifndef LAB8_ELEMENT_H
#define LAB8_ELEMENT_H

#endif //LAB8_ELEMENT_H

#include <string>

#define SIZE 10

using namespace std;

struct Node {
  string key;
  uint64_t val;
  
  Node();
  void Print();
};