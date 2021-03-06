#include<iostream>
#include<string.h>
#include <string>
#include <sstream>

using namespace std;

template <typename T>
class Queue {
private:
  T *arr;
  int size;
  int amount;
  T *begin;
  T *end;

public:
  Queue();
  explicit Queue(int size);
  bool push(T *value);
  bool pop(T *value);
  bool empty();
  bool full();
  void show();
};

template<typename T>
Queue<T>::Queue() { }

template <typename T>
Queue<T>::Queue(int size) {
  arr = new T[size];
  this->size = size;
  amount = 0;
  begin = arr;
  end = arr;
}

template <typename T>
bool Queue<T>::push(T *value) {
  // Check if there is any space left in the queue
  if (full()) {
    return false;
  }
  
  // Save the value
  *end = *value;
  
  // Move the end of the Queue to the next position
  if (end - arr + 1 == size) {
    end = arr;
  } else {
    ++end;
  }
  
  // Increment the amount
  ++amount;
  
  return true;
}

template <typename T>
bool Queue<T>::pop(T *value) {
  // Check if there is any value in the Queue
  if (empty()) {
    return false;
  }
  
  // Set the output value
  *value = *begin;
  
  // Move the begin of the Queue to the next position
  if (begin - arr + 1 == size) {
    begin = arr;
  } else {
    ++begin;
  }
  
  // Decrement the amount
  --amount;
  
  return true;
}

template <typename T>
bool Queue<T>::empty() {
  return 0 == amount;
}

template <typename T>
bool Queue<T>::full() {
  return size == amount;
}

template <typename T>
void Queue<T>::show() {
  T *current = begin;
  
  for (int i = 0; i < amount; ++i) {
    cout << *current << ',';
  
    if (current - arr + 1 == size) {
      current = arr;
    } else {
      ++current;
    }
  }
  
  cout << endl;
}

/*
int main() {
  Queue q(4);
  int i;

  cout << q.push(100) << endl;
  cout << q.push(2) << endl;
  q.show();
  cout << q.pop(&i) << " " << i << endl;
  cout << q.pop(&i) << " " << i << endl;
  q.show();
  cout << q.pop(&i) << " " << i << endl;
  cout << q.push(3) << endl;
  q.show();
  cout << q.push(4) << endl;
  cout << q.push(5) << endl;
  cout << q.push(6) << endl;
  cout << q.push(7) << endl;
  cout << q.push(8) << endl;

  cout << endl;

  q.show();

  cout << q.pop(&i) << " " << i << endl;
  cout << q.pop(&i) << " " << i << endl;

  cout << endl;
  q.show();

}
*/

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
      Queue<int> *tmp = new Queue<int>(value);
      queue[currentQ] = *tmp;
      delete tmp;
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