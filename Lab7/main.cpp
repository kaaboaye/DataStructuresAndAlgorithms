#include <iostream>
#include <string>
#include <sstream>

#ifndef nullptr
#define nullptr NULL
#endif


// BST

using namespace std;


struct Item{
  int key;
  int value;
  
  void Print();
};

void Item::Print() {
  cout <<
    key <<
    '(' <<
    value <<
    "),";
}

class BST {
  struct node {
    Item item;
    
    node *parent;
    node *smaller;
    node *greater;
  };
  
  node *head;

public:
  BST();
  bool Push(Item item);
  void ShowInorder();
  void ShowPreorder();
  void ShowPostorder();
  bool Find(int key, Item &item);
  bool Pop(int key, Item &item);
  void Clear();
  int Count();
  int Height();

private:
  node **min(node **n);
  node **max(node **n);
  void del(node **n);
  void delChildren(node *n);
  void countChildren(node *n, int &counter);
  int height(node *n);
  void showInorder(node *n);
  void showPreorder(node *n);
  void showPostorder(node *n);
};

BST::BST() {
  head = nullptr;
}

bool BST::Push(Item item) {
  if (!head) {
    head = new node;
    
    head->item = item;
    head->parent = nullptr;
    head->smaller = nullptr;
    head->greater = nullptr;
  
    return true;
  }
  
  node *n = head;
  
  while (true) {
    // if equal
    if (n->item.key == item.key) {
      return false;
    }
    
    // if smaller
    if (item.key < n->item.key) {
      if (!n->smaller) {
        n->smaller = new node;
        n->smaller->parent = n;
        n = n->smaller;
        
        n->item = item;
        n->smaller = nullptr;
        n->greater = nullptr;
  
        return true;
      }
      
      n = n->smaller;
      continue;
    }
    
    // if greater
    if (item.key > n->item.key) {
      if (!n->greater) {
        n->greater = new node;
        n->greater->parent = n;
        n = n->greater;
        
        n->item = item;
        n->smaller = nullptr;
        n->greater = nullptr;
  
        return true;
      }
      
      n = n->greater;
      continue;
    }
  }
}

void BST::ShowInorder() {
//  node *h = head;
//  node *n = head;
//
//  while (h) {
//    while (n->smaller) {
//      n = n->smaller;
//    }
//
//    while (true) {
//      n->item.Print();
//
//      if (n == h) {
//        break;
//      } else {
//        n = n->parent;
//      }
//    }
//
//    n = h = h->greater;
//  }
  
  showInorder(head);
  cout << endl;
}

void BST::ShowPreorder() {
  showPreorder(head);
  cout << endl;
}

void BST::ShowPostorder() {
  showPostorder(head);
  cout << endl;
}

bool BST::Find(const int key, Item &item) {
  node *n = head;
  
  while (n) {
    if (key == n->item.key) {
      item = n->item;
      return true;
    }
    
    if (key < n->item.key) {
      n = n->smaller;
      continue;
    }
    
    if (key > n->item.key) {
      n = n->greater;
      continue;
    }
  }
  
  return false;
}

bool BST::Pop(int key, Item &item) {
  node **n = &head;
  
  while (*n) {
    if (key == (**n).item.key) {
      item = (**n).item;
      del(n);
      
      return true;
    }
    
    if (key < (**n).item.key) {
      n = &(**n).smaller;
      continue;
    }
    
    if (key > (**n).item.key) {
      n = &(**n).greater;
      continue;
    }
  }
  
  return false;
}

void BST::del(BST::node **n) {
  // no children
  if (!(**n).greater && !(**n).smaller) {
    delete *n;
    *n = nullptr;
    return;
  }

  // only smaller
  if (!(**n).greater) {
    node *tmp = (**n).smaller;
    delete *n;
    *n = tmp;
    return;
  }

  // only greater
  if (!(**n).smaller) {
    node *tmp = (**n).greater;
    delete *n;
    *n = tmp;
    return;
  }

  // both children
  if ((**n).smaller && (**n).greater) {
    node **minNode = min(&(**n).greater);
    (**n).item = (**minNode).item;
    del(minNode);
    return;
  }
}

BST::node **BST::min(BST::node **n) {
  while ((**n).smaller) {
    n = &(**n).smaller;
  }
  
  return n;
}

BST::node **BST::max(BST::node **n) {
  while ((**n).greater) {
    n = &(**n).greater;
  }
  
  return n;
}

void BST::Clear() {
  delChildren(head);
  head = nullptr;
}

void BST::delChildren(node *n) {
  if (!n) {
    return;
  }
  
  delChildren(n->smaller);
  delChildren(n->greater);
  delete n;
}

int BST::Count() {
  int amount = 0;
  countChildren(head, amount);
  return amount;
}

void BST::countChildren(BST::node *n, int &counter) {
  if (!n) return;
  
  ++counter;
  countChildren(n->smaller, counter);
  countChildren(n->greater, counter);
}

int BST::Height() {
  return height(head);
}

int BST::height(BST::node *n) {
  if (!n) return 0;
  
  int smaller = height(n->smaller);
  int greater = height(n->greater);
  
  if (smaller > greater) {
    return smaller + 1;
  } else {
    return greater + 1;
  }
}

void BST::showInorder(BST::node *n) {
  if (!n) return;
  
  showInorder(n->smaller);
  n->item.Print();
  showInorder(n->greater);
}

void BST::showPreorder(BST::node *n) {
  if (!n) return;
  
  n->item.Print();
  showPreorder(n->smaller);
  showPreorder(n->greater);
}

void BST::showPostorder(BST::node *n) {
  if (!n) return;
  
  showPostorder(n->smaller);
  showPostorder(n->greater);
  n->item.Print();
}

void init(BST &tree){
}

bool insertElem(BST &tree, Item elem){
  return tree.Push(elem);
}

void showInorder(BST &tree){
  tree.ShowInorder();
}

void showPreorder(BST &tree){
  tree.ShowPreorder();
}

void showPostorder(BST &tree){
  tree.ShowPostorder();
}

bool findKey(BST &tree, int key, Item &elem){
  return tree.Find(key, elem);
}

bool removeKey(BST &tree, int key, Item &elem){
  return tree.Pop(key, elem);
}

void clear(BST &tree){
  tree.Clear();
}

int numberOfNodes(BST &tree){
  return tree.Count();
}

int height(BST &tree){
  return tree.Height();
}

void showBool(bool val){
  if(val)
    cout << "true" << endl;
  else
    cout << "false" << endl;
}

bool isCommand(const string &command,const char *mnemonic){
  return command==mnemonic;
}

int main(){
  string line;
  string command;
  BST *tree = nullptr;
  int currentT=0;
  int value;
  cout << "START" << endl;
  while(true){
    getline(cin,line);
    std::stringstream stream(line);
    stream >> command;
    if(line=="" || command[0]=='#')
    {
      // ignore empty line and comment
      continue;
    }
    
    // copy line on output with exclamation mark
    cout << "!" << line << endl;;
    
    // change to uppercase
    command[0]=toupper(command[0]);
    command[1]=toupper(command[1]);
    
    // zero-argument command
    if(isCommand(command,"HA")){
      cout << "END OF EXECUTION" << endl;
      break;
    }
    
    if(isCommand(command,"SI"))
    {
      showInorder(tree[currentT]);
      continue;
    }
    
    if(isCommand(command,"SP"))
    {
      showPreorder(tree[currentT]);
      continue;
    }
    
    if(isCommand(command,"SQ"))
    {
      showPostorder(tree[currentT]);
      continue;
    }
    
    if(isCommand(command,"CL"))
    {
      clear(tree[currentT]);
      continue;
    }
    
    if(isCommand(command,"IN"))
    {
      init(tree[currentT]);
      continue;
    }
    
    if(isCommand(command,"NN"))
    {
      cout << numberOfNodes(tree[currentT]) << endl;
      continue;
    }
    
    if(isCommand(command,"HE"))
    {
      cout << height(tree[currentT]) << endl;
      continue;
    }
    
    // read next argument, one int value
    stream >> value;
    
    
    if(isCommand(command,"IE"))
    {
      int variable2;
      stream >> variable2;
      Item elem;
      elem.key=value;
      elem.value=variable2;
      showBool(insertElem(tree[currentT],elem));
      continue;
    }
    
    if(isCommand(command,"FK"))
    {
      Item elem;
      bool ret=findKey(tree[currentT], value, elem);
      if(ret)
        cout << elem.key << '(' << elem.value << ')' << endl;
      else
        cout << "false" << endl;
      continue;
    }
    
    if(isCommand(command,"RK"))
    {
      Item elem;
      bool ret=removeKey(tree[currentT], value, elem);
      if(ret)
        cout << elem.key << '(' << elem.value << ')' << endl;
      else
        cout << "false" << endl;
      continue;
    }
    
    
    if(isCommand(command,"CH"))
    {
      currentT=value;
      continue;
    }
    
    if(isCommand(command,"GO"))
    {
      tree=new BST[value];
      continue;
    }
    
    cout << "wrong argument in test: " << command << endl;
    
  }
  return 0;
}