#include <iostream>
#include <string>
#include <sstream>

#ifndef nullptr
#define nullptr NULL
#endif

using namespace std;

struct item {
  int key;
  int value;
};

typedef struct item Item;

class List {
  struct listItem {
    Item item;
    listItem *next;
    listItem *prev;
  };
  
  listItem *sentinal;

public:
  List();
  ~List();

  void Push(Item &item);
  bool Find(int key, Item &item);
  void DelKeys(int key);
  void ShowHead();
  void ShowTail();
  void Clean();
  void Concat(List &list);

private:
  void pushAfter(Item &i, listItem *prev);
  void pushBefore(Item &i, listItem *next);
  bool pop(listItem *i);
  listItem *new_listItem(Item &i, listItem *n, listItem *p);
};

List::List() {
  sentinal = new listItem;
  sentinal->next = sentinal;
  sentinal->prev = sentinal;
}

List::~List() {
  Clean();
}

void List::Push(Item &item) {
  listItem *li = sentinal->next;
  
  while (li != sentinal) {
    if (li->item.key > item.key) {
      pushBefore(item, li);
      return;
    }
    
    li = li->next;
  }
  
  pushBefore(item, sentinal);
}

List::listItem *List::new_listItem(Item &i, listItem *n, listItem *p) {
  listItem *li;
  li = new listItem;
  li->item = i;
  li->next = n;
  li->prev = p;
  return li;
}

void List::pushAfter(Item &i, List::listItem *prev) {
  listItem *next = prev->next;
  
  prev->next = new_listItem(i, next, prev);
  next->prev = prev->next;
}

void List::pushBefore(Item &i, List::listItem *next) {
  listItem *prev = next->prev;
  
  prev->next = new_listItem(i, next, prev);
  next->prev = prev->next;
}

bool List::Find(int key, Item &item) {
  listItem *li = sentinal->next;
  
  while (li != sentinal) {
    if (li->item.key == key) {
      item = li->item;
      return true;
    }
    
    li = li->next;
  }
  
  return false;
}

void List::DelKeys(int key) {
  listItem *li = sentinal->next;
  
  while (li->item.key < key && li != sentinal) {
    li = li->next;
  }
  
  while (li->item.key == key && li != sentinal) {
    li = li->next;
    if (!pop(li->prev)) return;
  }
  
//  while (li != sentinal) {
//    if (li->item.key < key) {
//      continue;
//    }
//
//    if (li->item.key == key) {
//      if (!pop(li)) return;
//    }
//
//    if (li->item.key > key) {
//      return;
//    }
//
//    li = li->next;
//  }
}

void List::ShowHead() {
  listItem *li = sentinal->next;
  
  while (li != sentinal) {
    cout
      << li->item.key
      << '('
      << li->item.value
      << ')'
      << ',';
    
    li = li->next;
  }
  
  cout << endl;
}

void List::ShowTail() {
  listItem *li = sentinal->prev;
  
  while (li != sentinal) {
    cout
        << li->item.key
        << '('
        << li->item.value
        << ')'
        << ',';
    
    li = li->prev;
  }
  
  cout << endl;
}

void List::Clean() {
  while (pop(sentinal->next));
}

void List::Concat(List &list) {
  if (sentinal == sentinal->next) {
    delete sentinal;
    sentinal = list.sentinal;
    list.sentinal = new listItem;
    list.sentinal->next = sentinal;
    list.sentinal->prev = sentinal;
    return;
  }
  
  Item item;
  listItem *li = sentinal;
  
  while (true) {
    item = list.sentinal->next->item;
    
    if (!pop(list.sentinal->next)) {
      return;
    }
    
    while (li->item.key > item.key && li != li->next) {
      li = li->next;
    }
    
    pushAfter(item, li);
  }
}

bool List::pop(List::listItem *i) {
  if (i == i->next) {
    return false;
  }
  
  listItem *prev = i->prev;
  listItem *next = i->next;
  
  delete i;
  
  prev->next = next;
  next->prev = prev;
  
  return true;
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
  List *list = nullptr;
  int currentL=0;
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
    
    if(isCommand(command,"SH")) //*
    {
//      showListFromHead(list[currentL]);
      list[currentL].ShowHead();
      continue;
    }
    
    if(isCommand(command,"ST")) //*
    {
//      showListFromTail(list[currentL]);
      list[currentL].ShowTail();
      continue;
    }
    
    if(isCommand(command,"CL")) //*
    {
//      clearList(list[currentL]);
      list[currentL].Clean();
      continue;
    }
    
    if(isCommand(command,"IN")) //*
    {
//      init(list[currentL]);
      continue;
    }
    
    // read next argument, one int value
    stream >> value;
    
    if(isCommand(command,"FK"))
    {
//      Element elem;
      Item elem;
//      bool ret=findKey(list[currentL], value, elem);
      bool ret = list[currentL].Find(value, elem);
      if(ret)
        cout << elem.key << '(' << elem.value << ')' << endl;
      else
        cout << "false" << endl;
      continue;
    }
    
    if(isCommand(command,"RK"))
    {
//      removeAllKeys(list[currentL],value);
      list[currentL].DelKeys(value);
      continue;
    }
    
    if(isCommand(command,"CH"))
    {
      currentL=value;
      continue;
    }
    
    if(isCommand(command,"IE"))
    {
      int variable2;
      stream >> variable2;
      Item elem;
      elem.key=value;
      elem.value=variable2;
//      insertElem(list[currentL],elem);
      list[currentL].Push(elem);
      continue;
    }
    
    if(isCommand(command,"GO"))
    {
//      list=new List2W[value];
      list = new List[value];
      continue;
    }
    
    if(isCommand(command,"AD"))
    {
//      addList(list[currentL],list[value]);
      list[currentL].Concat(list[value]);
      continue;
    }
    cout << "wrong argument in test: " << command << endl;
  }
  return 0;
}