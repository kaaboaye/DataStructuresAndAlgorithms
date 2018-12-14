#include <iostream>
#include <string>

#ifndef nullptr
#define nullptr NULL
#endif

// BST

using namespace std;

template <typename K, typename V>
class BST {
  struct node_t {
    K key;
    V value;

    node_t *smaller;
    node_t *greater;

    node_t(K key, V value) {
      this->key = key;
      this->value = value;
      smaller = nullptr;
      greater = nullptr;
    }
  };

  node_t *head;

 public:
  BST() { head = nullptr; }

  void Push(K key, V value) {
    if (!head) {
      head = new node_t(key, value);
      return;
    }

    node_t *n = head;

    for (;;) {
      // if equal
      if (n->key == key) {
        n->value = value;
        return;
      }

      // if smaller
      if (n->key > key) {
        if (!n->smaller) {
          n->smaller = new node_t(key, value);
          return;
        }

        n = n->smaller;
        continue;
      }

      // if greater
      if (n->key < key) {
        if (!n->greater) {
          n->greater = new node_t(key, value);
          return;
        }

        n = n->greater;
        continue;
      }
    }
  }

  bool Find(K key, V &value) {
    node_t *n = head;

    while (n) {
      if (key == n->key) {
        value = n->value;
        return true;
      }

      if (n->key > key) {
        n = n->smaller;
        continue;
      }

      if (n->key < key) {
        n = n->greater;
        continue;
      }
    }

    return false;
  }
};

template <typename K, typename V>
void try_find(BST<K, V> &bst, K key) {
  K ref;

  if (bst.Find(key, ref)) {
    std::cout << ref << std::endl;
  } else {
    std::cout << "not found" << std::endl;
  }
}

#define try_find_string try_find<std::string, std::string>

void test_string() {
  BST<std::string, std::string> bst;

  bst.Push("key", "val");
  bst.Push("1", "jeden");
  bst.Push("2", "dwa");
  bst.Push("3", "trzy");

  try_find_string(bst, "key");
  try_find_string(bst, "knjdfbnfgbhjfsdbhgjhjbdfshjdfs");
  try_find_string(bst, "key");
  try_find_string(bst, "1");
  try_find_string(bst, "2");
  try_find_string(bst, "3");

  bst.Push("key", "new val");
  try_find_string(bst, "key");
}

#define try_find_int try_find<int, int>

void test_int() {
  BST<int, int> bst;

  bst.Push(1, 10);
  bst.Push(2, 20);
  bst.Push(3, 30);

  try_find_int(bst, 1);
  try_find_int(bst, 0xDEADC0DE);
  try_find_int(bst, 2);
  try_find_int(bst, 3);

  bst.Push(3, 33);
  try_find_int(bst, 3);
}

int main() {
  std::cout << "testing string, string" << std::endl << std::endl;
  test_string();
  std::cout << std::endl << "testing int int" << std::endl << std::endl;
  test_int();
}