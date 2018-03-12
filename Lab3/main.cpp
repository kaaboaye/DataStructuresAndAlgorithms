#include <iostream>
#include <string>
#include <sstream>

#ifndef nullptr
#define nullptr NULL
#endif

using namespace std;

template <typename T>
class DoubleLinkedList {
  struct Item {
    T Value;
    Item *next;
    Item *prev;
  };
  
  Item *head;

public:
  DoubleLinkedList();
  ~DoubleLinkedList();
  
  void PushHead(T &value);
  bool PopHead(T &value);
  void PushTail(T &value);
  bool PopTail(T &value);
  int GetPossition(T &value);
  bool DelValue(T &value);
  void DelValues(T &value);
  void PrintHead();
  void PrintTail();
  void Clear();
  void Join(DoubleLinkedList<T> list);
};

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList() {
  head = nullptr;
}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
  Clear();
}

template<typename T>
void DoubleLinkedList<T>::PushHead(T &value) {
  if (!head) {
    head = new Item;
    head->Value = value;
    head->next = head;
    head->prev = head;
    return;
  }
  
  Item *oldHead = head;
  
  head = new Item;
  head->Value = value;
  head->next = oldHead;
  head->prev = oldHead->prev;
  
  oldHead->prev->next = head;
  
  oldHead->prev = head;
}

template<typename T>
bool DoubleLinkedList<T>::PopHead(T &value) {
  if (!head) {
    return false;
  }
  
  value = head->Value;
  
  Item *newHead;
  
  newHead = head->next;
  
  // x <- []
  newHead->prev = head->prev;
  
  // [] -> x
  newHead->next = head->next;
  
  delete head;
  head = newHead;
  
  return true;
}

template<typename T>
void DoubleLinkedList<T>::PushTail(T &value) {
  if (!head) {
    PushHead(value);
    return;
  }
  
  Item *oldTail = head->prev;
  Item *newTail = new Item;
  newTail->Value = value;
  newTail->prev = oldTail;
  newTail->next = head;
  
  head->prev = newTail;
  oldTail->next = newTail;
}

template<typename T>
bool DoubleLinkedList<T>::PopTail(T &value) {
  if (!head) {
    return false;
  }
  
  Item *oldTail = head->prev;
  
  value = oldTail->Value;
  
  head->prev = oldTail->prev;
  head->prev->next = head;
  
  delete oldTail;
  return true;
}

template<typename T>
int DoubleLinkedList<T>::GetPossition(T &value) {
  if (!head) {
    return -1;
  }
  
  Item *it = head;
  int pos = 0;
  
  while (true) {
    if (it->Value == value) {
      return pos;
    }
    
    if (it->next == head) {
      return -1;
    }
    
    ++pos;
    it = it->next;
  }
}

template<typename T>
bool DoubleLinkedList<T>::DelValue(T &value) {
  if (!head) {
    return false;
  }
  
  Item *it = head;
  
  while (true) {
    if (it->Value == value) {
      it->next->prev = it->prev;
      it->prev->next = it->next;
      delete it;
  
      return true;
    }
    
    if (it->next == head) {
      return false;
    }
    
    it = it->next;
  }
}

template<typename T>
void DoubleLinkedList<T>::DelValues(T &value) {
  while (DelValue(value));
}

template<typename T>
void DoubleLinkedList<T>::PrintHead() {
  if (!head) {
    cout << endl;
    return;
  }
  
  Item *it = head;
  
  while (true) {
    cout << it->Value << ',';
    
    if (it->next == head) {
      cout << endl;
      return;
    }
  
    it = it->next;
  }
}

template<typename T>
void DoubleLinkedList<T>::PrintTail() {
  if (!head) {
    cout << endl;
    return;
  }
  
  Item *it = head->prev;
  
  while (true) {
    cout << it->Value << ',';
    
    if (it == head) {
      cout << endl;
      return;
    }
    
    it = it->prev;
  }
}

template<typename T>
void DoubleLinkedList<T>::Clear() {
  if (!head) {
    return;
  }
  
  Item *p = head;
  Item *tmp;
  head->prev->next = nullptr;
  
  while (p) {
    tmp = p;
    p = p->next;
    delete tmp;
  }
  
  head = nullptr;
}

template<typename T>
void DoubleLinkedList<T>::Join(DoubleLinkedList<T> list) {
  T val;
  
  while (list.PopHead(val)) {
    PushTail(val);
  }
}

void showBool(bool val){
  if(val)
    cout << "true" << endl;
  else
    cout << "false" << endl;
}

bool isCommand(const string command,const char *mnemonic){
  return command==mnemonic;
}

int main(){
  string line;
  string command;
  DoubleLinkedList<int> *list;
  int currentL=0;
  int value;
  cout << "START" << endl;
  while(true){
    getline(cin,line);
    stringstream stream(line);
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
    
    if(isCommand(command,"HA")){
      cout << "END OF EXECUTION" << endl;
      break;
    }
    
    
    // zero-argument command
    if(isCommand(command,"DH")) //*
    {
      int retValue;
//      bool retBool=deleteHead(list[currentL],retValue);
      bool retBool = list[currentL].PopHead(retValue);
      if(retBool)
        cout << retValue << endl;
      else
        showBool(retBool);
      continue;
    }
    if(isCommand(command,"DT")) //*
    {
      int retValue;
//      bool retBool=deleteTail(list[currentL],retValue);
      bool retBool = list[currentL].PopTail(retValue);
      if(retBool)
        cout << retValue << endl;
      else
        showBool(retBool);
      continue;
    }
    
    if(isCommand(command,"SH")) //*
    {
//      showListFromHead(list[currentL]);
      list[currentL].PrintHead();
      continue;
    }
    
    if(isCommand(command,"ST")) //*
    {
//      showListFromTail(list[currentL]);
      list[currentL].PrintTail();
      continue;
    }
    
    if(isCommand(command,"CL")) //*
    {
//      clearList(list[currentL]);
      list[currentL].Clear();
      continue;
    }
    
    if(isCommand(command,"IN")) //*
    {
//      init(list[currentL]);
      DoubleLinkedList<int> *tmp = new DoubleLinkedList<int>();
      list[currentL] = *tmp;
      delete tmp;
      continue;
    }
    
    // read next argument, one int value
    stream >> value;
    
    if(isCommand(command,"FV")) //*
    {
      int ret;
//      ret=findValue(list[currentL],value);
      ret = list[currentL].GetPossition(value);
      cout << ret << endl;
      continue;
    }
    
    if(isCommand(command,"RV")) //*
    {
//      removeAllValue(list[currentL],value);
      list[currentL].DelValues(value);
      continue;
    }
    
    
    if(isCommand(command,"AD")) //*
    {
//      addList(list[currentL],list[value]);
      list[currentL].Join(list[value]);
      continue;
    }
    
    if(isCommand(command,"CH")) //*
    {
      currentL=value;
      continue;
    }
    
    if(isCommand(command,"IH")) //*
    {
//      insertHead(list[currentL],value);
      list[currentL].PushHead(value);
      continue;
    }
    
    if(isCommand(command,"IT")) //*
    {
//      insertTail(list[currentL],value);
      list[currentL].PushTail(value);
      continue;
    }
    
    if(isCommand(command,"GO")) //*
    {
//      list=new List2W[value];
      list = new DoubleLinkedList<int>[value];
      continue;
    }
    
    cout << "wrong argument in test: " << command << endl;
  }
}