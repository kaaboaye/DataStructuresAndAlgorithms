#include <iostream>
#include <regex>
#include <sstream>
#include <fstream>
#include "Counter.h"
#include "HashTable.h"
#include "BST.h"
#include "BalancedBST.h"
#include "UnsortedVector.h"

int main() {
  Counter *c;
  int opt;
  
  ask:
  cout <<
       "1) BST" << endl <<
       "2) Balanced BST" << endl <<
       "3) HashTable" << endl <<
       "4) UnsortedVector" << endl <<
       "Structure: ";

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
  cout << c->MostPopular() << endl;
  
  clock_t t1 = clock();
  double t = (double) (t1 - t0) / (double) CLOCKS_PER_SEC;
  cout << "Execution time: " << t << " seconds" << endl;
  
  return 0;
}