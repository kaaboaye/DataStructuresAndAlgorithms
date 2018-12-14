#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include "BST.h"
#include "BalancedBST.h"
#include "Counter.h"
#include "HashTable.h"
#include "UnsortedVector.h"
#include "WordMap.h"
#include "llist.h"

int main() {
  Counter *c;
  int opt;

ask:
  cout << "1) BST" << endl
       << "2) Balanced BST" << endl
       << "3) HashTable" << endl
       << "4) UnsortedVector" << endl
       << "5) WordMap" << endl
       << "6) Linked list" << endl
       << "Structure: ";

  cin >> opt;
  switch (opt) {
    case 1:
      c = new BST();
      break;

    case 2:
      c = new BalancedBST();
      break;

    case 3:
      c = new HashTable();
      break;

    case 4:
      c = new UnsortedVector();
      break;

    case 5:
      c = new WordMap();
      break;

    case 6:
      c = new LList();
      break;

    default:
      goto ask;
  }

  // Load
  string filename;
  cout << "Filename: ";
  cin >> filename;
  ifstream file(filename);
  if (!file.good()) {
    cout << "Cannot open file " << filename << endl;
    return 0;
  }

  clock_t t0 = clock();

  //  cout << file.rdbuf();
  c->Load(file);
  c->MostPopular();
  c->Print();

  clock_t t1 = clock();
  double t = (double)(t1 - t0) / (double)CLOCKS_PER_SEC;
  cout << "Execution time: " << t << " seconds" << endl;

  return 0;
}