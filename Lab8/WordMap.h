//
// Created by Mieszko Wawrzyniak on 17/05/2018.
//

#ifndef LAB8_WORDMAP_H
#define LAB8_WORDMAP_H


#include "Counter.h"

#define _WordMap_Node_Arr_Size ('z' - 'a' + 1)

class WordMap: public Counter {
  struct _Node {
    _Node *branches[_WordMap_Node_Arr_Size];
    uint64_t val;
    
    _Node();
  };
  
  _Node *root;

public:
  WordMap();
  void Add(string word) override;
  void MostPopular() override;

private:
  void walk(_Node *node, string &s);
//  void walk(_Node *node, const char *s, char *c);
};


#endif //LAB8_WORDMAP_H
