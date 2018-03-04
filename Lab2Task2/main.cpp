#include <iostream>
#include <sstream>

#define nullptr NULL

using namespace std;

template <typename T>
class List {
  struct Item {
    T Value;
    Item *next;
  };
  
  Item *head;

public:
  List();
  ~List();
  
  void PushHead(T *value);
  bool PopHead(T *value);
  void PushTail(T *value);
  bool PopTail(T *value);
  int FindValue(const T *value);
  bool DeleteValue(const T *value);
  bool GetValue(int id, T *value);
  void Show();
  void Clear();

private:
  void *getTail();
};

template<typename T>
List<T>::List() {
  head = nullptr;
}

template<typename T>
void List<T>::PushHead(T *value) {
  // If List is empty
  if (!head) {
    head = new Item;
    head->Value = *value;
    head->next = nullptr;
    return;
  }
  
  Item *old = head;
  head = new Item;
  head->Value = *value;
  head->next = old;
}

template<typename T>
bool List<T>::PopHead(T *value) {
  // If List is empty
  if (!head) {
    return false;
  }
  
  // Set output value
  *value = head->Value;
  
  // Set new head
  {
    Item *old;
    old = head;
    head = head->next;
    delete old;
  }
  
  return true;
}

template<typename T>
void List<T>::PushTail(T *value) {
  // If Empty List
  if (!head) {
    head = new Item;
    head->Value = *value;
    head->next = nullptr;
    return;
  }
  
  Item *tail = (Item*) getTail();
  tail->next = new Item;
  tail->next->Value = *value;
  tail->next->next = nullptr;
}

template<typename T>
bool List<T>::PopTail(T *value) {
  // If List is empty
  if (!head) {
    return false;
  }
  
  // If wónż jest głowoogonem
  if (!head->next) {
    *value = head->Value;
    delete head->next;
    head->next = nullptr;
    return true;
  }
  
  
  Item *newTail = head;
  while (newTail->next->next) {
    newTail = newTail->next;
  }
  
  *value = newTail->next->Value;
  delete newTail->next;
  newTail->next = nullptr;
  return true;
}

template<typename T>
int List<T>::FindValue(const T *value) {
  // If List is empty
  if (!head) {
    return -1;
  }
  
  int id = 0;
  Item *item = head;
  do {
    if (*value == item->Value) {
      return id;
    }
    
    ++id;
  } while ((item = item->next));
  
  return -1;
}

template<typename T>
bool List<T>::DeleteValue(const T *value) {
  // If List is empty
  if (!head) {
    return false;
  }
  
  // If wónż jest głowoogonem
  if (!head->next) {
    if (*value == head->Value) {
      delete head;
      head = nullptr;
      return true;
    }
  
    return false;
  }
  
  Item *prev = head;
  
  do {
    if (*value != prev->next->Value) {
      continue;
    }
    
    Item *next = prev->next->next;
    delete prev->next;
    prev->next = next;
    return true;
  } while ((prev = prev->next));
  
  return false;
}

template<typename T>
bool List<T>::GetValue(const int id, T *value) {
  // If List is empty
  if (!head) {
    return false;
  }
  
  int i = 0;
  Item *item = head;
  do {
    if (id == i) {
      *value = item->Value;
      return true;
    }
    ++i;
  } while ((item = item->next));
  
  return false;
}

template<typename T>
void List<T>::Show() {
  if (!head) {
    cout << endl;
    return;
  }
 
  Item *i = head;
  do {
    cout << i->Value << ',';
  } while ((i = i->next));
  
  cout << endl;
}


template<typename T>
void *List<T>::getTail() {
  // If List is empty
  if (!head) {
    return nullptr;
  }

  Item *tail = head;
  while (tail->next) {
    tail = tail->next;
  }

  return tail;
}

template<typename T>
void List<T>::Clear() {
  Item *p = head;
  Item *tmp;
  while (p) {
    tmp = p;
    p = p->next;
    delete tmp;
  }
}

template<typename T>
List<T>::~List() {
  Clear();
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
  List<int> *list=NULL;
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
    
    if(isCommand(command,"HA")){
      cout << "END OF EXECUTION" << endl;
      break;
    }
    
    
    // zero-argument command
    if(isCommand(command,"DH"))
    {
      int retValue;
//      bool retBool=deleteHead(list[currentL],retValue);
      bool retBool = list[currentL].PopHead(&retValue);
      if(retBool)
        cout << retValue << endl;
      else
        showBool(retBool);
      continue;
    }
    if(isCommand(command,"DT"))
    {
      int retValue;
//      bool retBool=deleteTail(list[currentL],retValue);
      bool retBool = list[currentL].PopTail(&retValue);
      if(retBool)
        cout << retValue << endl;
      else
        showBool(retBool);
      continue;
    }
    
    if(isCommand(command,"SH"))
    {
//      showListFromHead(list[currentL]);
      list[currentL].Show();
      continue;
    }
    
    if(isCommand(command,"CL"))
    {
//      clearList(list[currentL]);
      list[currentL].Clear();
      continue;
    }
    
    if(isCommand(command,"IN"))
    {
//      init(list[currentL]);
      List<int> *tmp = new List<int>();
      list[currentL] = *tmp;
      delete tmp;
      continue;
    }
    
    // read next argument, one int value
    stream >> value;
    
    if(isCommand(command,"FP"))
    {
      int ret;
//      ret=findPosOfValue(list[currentL],value);
      ret = list[currentL].FindValue(&value);
      cout << ret << endl;
      continue;
    }
    
    if(isCommand(command,"DV"))
    {
//      showBool(deleteValue(list[currentL],value));
      showBool(list[currentL].DeleteValue(&value));
      continue;
    }
    
    
    if(isCommand(command,"AT"))
    {
      int retValue;
//      bool retBool=atPosition(list[currentL],value,retValue);
      bool retBool = list[currentL].GetValue(value, &retValue);
      if(retBool)
        cout << retValue << endl;
      else
        showBool(retBool);
      continue;
    }
    
    if(isCommand(command,"CH"))
    {
      currentL=value;
      continue;
    }
    
    if(isCommand(command,"IH"))
    {
//      insertHead(list[currentL],value);
      list[currentL].PushHead(&value);
      continue;
    }
    
    if(isCommand(command,"IT"))
    {
//      insertTail(list[currentL],value);
      list[currentL].PushTail(&value);
      continue;
    }
    
    if(isCommand(command,"GO"))
    {
      list=new List<int>[value];
      continue;
    }
    
    cout << "wrong argument in test: " << command << endl;
  }
}