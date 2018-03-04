#include <iostream>
#include <string.h>
#include <string>
#include <sstream>

using namespace std;

template <typename T>
class Queue {
  T *arr;
  int length;
  int amount;

public:
  Queue();
  explicit Queue(int size);
  
  bool push(T *value);
  bool pop(T *value);
  bool full();
  bool empty();
  void show();
  
  ~Queue();
};

template<typename T>
Queue<T>::Queue() { }

template<typename T>
Queue<T>::Queue(int size) {
  arr = new T[size];
  length = size;
  amount = 0;
}

template<typename T>
bool Queue<T>::push(T *value) {
  if (full()) {
    return false;
  }
  
  arr[amount++] = *value;
  return true;
}

template<typename T>
bool Queue<T>::pop(T *value) {
  if (empty()) {
    return false;
  }
  
  *value = *arr;
  
  for (int i = 1; i < amount; ++i) {
    arr[i-1] = arr[i];
  }
  
  --amount;
  
  return true;
}

template<typename T>
bool Queue<T>::empty() {
  return 0 == amount;
}

template<typename T>
bool Queue<T>::full() {
  return length == amount;
}

template<typename T>
void Queue<T>::show() {
  for (int i = 0; i < amount; ++i) {
    cout << arr[i] << ',';
  }
  
  cout << endl;
}

template<typename T>
Queue<T>::~Queue() {
  delete arr;
}

//int main() {
//  Queue<int> q(3);
//  int arr[] = {0,1,2,3,4,5,6,7,8,9};
//  int *i = arr;
//  int n;
//
//  cout << q.push(i) << '\t'; q.show();
//  cout << q.push(++i) << '\t'; q.show();
//  cout << q.pop(&n) << '\t' << n << '\t'; q.show();
//  cout << q.push(++i) << '\t'; q.show();
//  cout << q.push(++i) << '\t'; q.show();
//
//  cout << q.pop(&n) << '\t' << n << '\t'; q.show();
//  cout << q.pop(&n) << '\t' << n << '\t'; q.show();
//  cout << q.pop(&n) << '\t' << n << '\t'; q.show();
//
//
//  return 0;
//}


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
  Queue<int> *queue=NULL;
  int currentQ=0;
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
    if(isCommand(command,"EM"))
    {
//      showBool(isEmpty(queue[currentQ]));
      showBool(queue[currentQ].empty());
      continue;
    }
    if(isCommand(command,"FU"))
    {
//      showBool(isFull(queue[currentQ]));
      showBool(queue[currentQ].full());
      continue;
    }
    if(isCommand(command,"SH"))
    {
//      show(queue[currentQ]);
      queue[currentQ].show();
      continue;
    }
    if(isCommand(command,"DE"))
    {
      int ret;
//      bool retBool=dequeue(queue[currentQ],ret);
      bool retBool = queue[currentQ].pop(&ret);
      if(!retBool)
        cout << "false" << endl;
      else
        cout << ret << endl;
      continue;
    }
    
    // read next argument, one int value
    stream >> value;
    
    if(isCommand(command,"GO"))
    {
      queue=new Queue<int>[value];
      continue;
    }
    if(isCommand(command,"CH"))
    {
      currentQ=value;
      continue;
    }
    
    if(isCommand(command,"IN"))
    {
//      init(queue[currentQ],value);
      queue[currentQ] = *new Queue<int>(value);
      continue;
    }
    
    if(isCommand(command,"EN"))
    {
//      bool retBool=enqueue(queue[currentQ],value);
      bool retBool = queue[currentQ].push(&value);
      showBool(retBool);
      continue;
    }
    cout << "wrong argument in test: " << command << endl;
  }
}