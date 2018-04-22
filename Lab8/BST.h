//
// Created by Mieszko Wawrzyniak on 22/04/2018.
//

#ifndef LAB8_BST_H
#define LAB8_BST_H


#include "Counter.h"

class BST: public Counter {
  struct _Node {
    string key;
    uint64_t val;
    
    _Node *left;
    _Node *right;
  
    explicit _Node(string key);
  };
  
  _Node *root;
  
public:
  BST();
  void Add(string word) override;
  string MostPopular() override;

private:
  void walk(_Node *node, string &topStr, uint64_t &topVal);
};


#endif //LAB8_BST_H
