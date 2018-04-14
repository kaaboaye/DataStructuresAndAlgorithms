#include<iostream>
#include <string>
#include <sstream>

using namespace std;

class Heap {
  
  int *arr;
  int size;
  int pos;

public:
  explicit Heap(int size);
  void Load(int amount);
  void Push(int value);
  void Sort();

private:
  void fixHeap();
  void hepify(int node);
  int parent(int node);
  int childLeft(int node);
  int childRight(int node);
  
  friend void show(Heap *h);
  
};

Heap::Heap(int size) {
  this->arr = new int[size];
  this->size = size;
  this->pos = 0;
}

void Heap::Load(int amount) {
  // maybe throw some exception when (amount > size)

  pos = amount;
  
  int *arr = this->arr;
  const int *passed = arr + pos;
  
  while (arr != passed) {
    cin >> *arr++;
  }
  
  fixHeap();
}

void Heap::Push(int value) {
  int node = pos++;
  int p;
  
  arr[node] = value;
  
  do {
    p = parent(node);
    
    if (arr[p] < arr[node]) {
      swap(arr[p], arr[node]);
    } else {
      break;
    }
    
    node = p;
    
  } while (node);
}

void Heap::Sort() {
  const int realPos = pos;
  --pos;

  while (pos) {
    swap(arr[0], arr[pos]);
    hepify(0);
    --pos;
  }

  pos = realPos;
}

void Heap::fixHeap() {
  for (int node = pos / 2; node >= 1; --node) {
    hepify(node - 1);
  }
}

void Heap::hepify(int node) {
  int nextNode;
  int left = childLeft(node);
  int right = childRight(node);
  
  if (left < pos && arr[left] > arr[node]) {
    nextNode = left;
  } else {
    nextNode = node;
  }

  if (right < pos && arr[right] > arr[nextNode]) {
    nextNode = right;
  }
  
  if (node != nextNode) {
    swap(arr[node], arr[nextNode]);
    hepify(nextNode);
  }
}

int Heap::childLeft(int node) {
  return 2 * node + 1;
}

int Heap::childRight(int node) {
  return 2 * node + 2;
}

void show(Heap *h){
  for(int i=0; i < h->pos; ++i)
  {
    cout << h->arr[i] << ",";
  }
  cout << endl;
}

int Heap::parent(int node) {
  return (node - 1) / 2;
}

// Glue

void init(Heap **h, int size){
  *h = new Heap(size);
}

void loadAndMakeHeap(Heap *h, int howMany){
  h->Load(howMany);
}

void add(Heap *h, int value){
  h->Push(value);
}

void makeSorted(Heap *h){
  h->Sort();
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
      init(&heap[currentH],value);
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