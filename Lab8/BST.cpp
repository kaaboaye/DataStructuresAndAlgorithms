//
// Created by Mieszko Wawrzyniak on 22/04/2018.
//

#include "BST.h"

#include <utility>
#include <iostream>

using namespace std;

BST::BST() {
  root = nullptr;
}

BST::_Node::_Node(string key) {
  this->key = move(key);
  this->val = 1;
  this->left = nullptr;
  this->right = nullptr;
}

void BST::Add(string word) {
  if (!root) {
    root = new _Node(word);
    return;
  }
  
  _Node *n = root;
  int cmp;
  
  while (true) {
    cmp = strcmp(n->key.c_str(), word.c_str());
    
    if (0 == cmp) {
      ++n->val;
      return;
    }
  
    if (cmp < 0) {
      if (!n->left) {
        n->left = new _Node(word);
        return;
      }
    
      n = n->left;
      continue;
    }
    
    if (cmp > 0) {
      if (!n->right) {
        n->right = new _Node(word);
        return;
      }
    
      n = n->right;
      continue;
    }
  }
}

void BST::MostPopular() {
  walk(root);
}

void BST::walk(BST::_Node *node) {
  if (!node) {
    return;
  }
  
  for (int i = 0; i < SIZE; ++i) {
    if (node->val <= arr[i].val) continue;
    
    for (int j = SIZE - 1; j > i; --j) {
      arr[j] = arr[j - 1];
    }
    
    arr[i].key = node->key;
    arr[i].val = node->val;
    
    break;
  }
  
  walk(node->left);
  walk(node->right);
}

void BST::counter(BST::_Node *n, int &c) {
  if (!n) {
    return;
  }
  
  ++c;
  
  counter(n->left, c);
  counter(n->right, c);
  
}

int BST::height(BST::_Node *n) {
  
  if (!n) return 0;
  
  int smaller = height(n->left);
  int greater = height(n->right);
  
  if (smaller > greater) {
    return smaller + 1;
  } else {
    return greater + 1;
  }
}
