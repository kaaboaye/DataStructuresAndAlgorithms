//
// Created by Mieszko Wawrzyniak on 22/04/2018.
//

#include "llist.h"
#include <string.h>
#include <string>

using namespace std;

LList::LList() { head = nullptr; }

void LList::Add(string word) {
  if (!head) {
    head = new _Elem(word);
    return;
  }

  _Elem* it;
  for (it = head; it != nullptr; it = it->next) {
    int cmp = strcmp(it->word.c_str(), word.c_str());

    if (cmp == 0) {
      ++it->num;
      return;
    }

    if (cmp < 0) {
      _Elem* next = it->next;
      it->next = new _Elem(word);
      it->next->next = next;
      return;
    }
  }

  it = new _Elem(word);
}

void LList::MostPopular() {
  string topStr;
  uint64_t topAmount = 0;

  for (_Elem* it = head; it != nullptr; it = it->next) {
    for (int i = 0; i < SIZE; ++i) {
      if (it->num <= arr[i].val) continue;

      for (int j = SIZE - 1; j > i; --j) {
        arr[j] = arr[j - 1];
      }

      arr[i].key = it->word;
      arr[i].val = it->num;

      break;
    }
  }
}

LList::_Elem::_Elem(string word) {
  this->word = move(word);
  this->num = 1;
  this->next = nullptr;
}
