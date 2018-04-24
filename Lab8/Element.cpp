//
// Created by Mieszko Wawrzyniak on 22/04/2018.
//

#include <iostream>
#include "Element.h"

Node::Node() {
  val = 0;
}

void Node::Print() {
  cout << key << " " << val << endl;
}
