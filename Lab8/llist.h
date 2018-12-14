//
// Created by Mieszko Wawrzyniak on 22/04/2018.
//

#ifndef LAB8_LLIST_H
#define LAB8_LLIST_H

#include <vector>
#include "Counter.h"

using namespace std;

class LList : public Counter {
  struct _Elem {
    string word;
    uint64_t num;
    _Elem *next;

    explicit _Elem(string word);
  };

  _Elem *head;

 public:
  LList();
  void Add(string word) override;
  void MostPopular() override;
};

#endif  // LAB8_LLIST_H
