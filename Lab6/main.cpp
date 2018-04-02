#include<iostream>
#include <string>
#include <sstream>

using namespace std;

class Heap {
  friend void show(Heap *h);
  
  int *arr;
  int size;
  int pos;

public:
  explicit Heap(int size);
  void Load(int amount);
  void Hepify();
};

void show(Heap *h){
  for(int i=0;i<h->pos;i++)
  {
    cout << h->arr[i] << ",";
  }
  cout << endl;
}

Heap::Heap(int size) {
  this->arr = new int[size];
  this->size = size;
  this->pos = 0;
}

void Heap::Load(int amount) {
  int *arr = this->arr;
  const int *passed = arr + amount;
  
  while (arr != passed) {
    cin >> *arr++;
  }
}

void Heap::Hepify() {

}

void init(Heap *&h, int size){
  h = new Heap(size);
}

//void heapAdjustment(Heap &h){
//}

void loadAndMakeHeap(Heap *h, int howMany){
}


void add(Heap *h, int value){
}


void makeSorted(Heap *h){
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
  Heap **heap;
  int currentH=0;
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
      show(heap[currentH]);
      continue;
    }
    
    if(isCommand(command,"MS")) //*
    {
      makeSorted(heap[currentH]);
      continue;
    }
    
    // read next argument, one int value
    stream >> value;
    
    if(isCommand(command,"IN")) //*
    {
      init(heap[currentH],value);
      continue;
    }
    
    if(isCommand(command,"LD"))
    {
      loadAndMakeHeap(heap[currentH],value);
      continue;
    }
    
    if(isCommand(command,"AD"))
    {
      add(heap[currentH],value);
      continue;
    }
    
    if(isCommand(command,"CH"))
    {
      currentH=value;
      continue;
    }
    
    if(isCommand(command,"GO"))
    {
      heap=new Heap*[value];
      continue;
    }
    
    cout << "wrong argument in test: " << command << endl;
  }
  return 0;
}