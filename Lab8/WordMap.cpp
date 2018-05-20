//
// Created by Mieszko Wawrzyniak on 17/05/2018.
//

#include "WordMap.h"

#define select(c) ((int) ((c) - 'a'))
#define getC(id) ((char) ('a' + (id)))

WordMap::WordMap() {
  root = new _Node;
}

void WordMap::Add(string word) {
  _Node *node = root;
  
  for (const char &c : word) {
    if (!node->branches[select(c)]) {
      node->branches[select(c)] = new _Node();
    }
    
    node = node->branches[select(c)];
  }
  
  ++node->val;
}

void WordMap::MostPopular() {
  char s[250];
  s[0] = 0;
  walk(root, s, 0);
}

void WordMap::walk(_Node *node, char *s, int id) {
  // Match
  if (node->val > 0) {
    for (int i = 0; i < SIZE; ++i) {
      if (node->val <= arr[i].val) continue;
    
      for (int j = SIZE - 1; j > i; --j) {
        arr[j] = arr[j - 1];
      }
    
      arr[i].key = string(s);
      arr[i].val = node->val;
    
      break;
    }
  }
  
  // Go on
  for (int i = 0; i < _WordMap_Node_Arr_Size; ++i) {
    s[id] = getC(i);
    s[++id] = 0;
    
    if (node->branches[i]) {
      walk(node->branches[i], s, id);
    }
  }
}

WordMap::_Node::_Node() {
  memset(this, 0, sizeof(_Node));
}
