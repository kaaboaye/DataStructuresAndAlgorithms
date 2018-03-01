#include<iostream>
#include<string.h>
#include <string>
#include <sstream>

using namespace std;

class Queue {
private:
  int *arr;
  int size;
  int amount;
  int *begin;
  int *end;

public:
  explicit Queue(int size);
  bool push(int value);
  bool pop(int *value);
  bool empty();
  bool full();
  void show();
};

Queue::Queue(int size) {
  arr = new int[size];
  this->size = size;
  amount = 0;
  begin = arr;
  end = arr;
}

bool Queue::push(int value) {
  // Check if there is any space left in the queue
  if (full()) {
    return false;
  }
  
  // Save the value
  *end = value;
  
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

bool Queue::pop(int *value) {
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

bool Queue::empty() {
  return 0 == amount;
}

bool Queue::full() {
  return size == amount;
}

void Queue::show() {
  int *current = begin;
  
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
  
  Queue *queue=NULL;
  
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
      showBool(queue->empty());
      continue;
    }
    if(isCommand(command,"FU"))
    {
      showBool(queue->full());
      continue;
    }
    if(isCommand(command,"SH"))
    {
      queue->show();
      continue;
    }
    if(isCommand(command,"DE"))
    {
      int ret;
      bool retBool=queue->pop(&ret);
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
      queue=new Queue(value);
      continue;
    }
    if(isCommand(command,"CH"))
    {
      currentQ=value;
      continue;
    }
    
    if(isCommand(command,"IN"))
    {
      queue = new Queue(value);
      continue;
    }
    
    if(isCommand(command,"EN"))
    {
      bool retBool= queue->push(value);
      showBool(retBool);
      continue;
    }
    cout << "wrong argument in test: " << command << endl;
  }
}
