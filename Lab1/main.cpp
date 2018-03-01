#include <iostream>
#include <string>
#include <sstream>


using namespace std;


void drawChars(const int n, const char c = 'X') {
  for (int i = 0; i < n; ++i) {
    cout << c;
  }
}

void drawTriangle(const int n) {
  for (int row = 1; row <= n; ++row) {
    drawChars(row);
    cout << endl;
  }
}


void drawSquare(const int n) {
  drawChars(n);
  cout << endl;
  
  for (int row = 0; row < n - 2; ++ row) {
    cout << "X";
    drawChars(n - 2, ' ');
    cout << "X" << endl;
  }
  
  drawChars(n);
  cout << endl;
}

void drawPyramid(const int n, const int shift = 0) {
  for (int row = 1; row <= n; ++row) {
    drawChars(n - row + shift, ' ');
    drawChars(2 * row - 1);
    
    cout << endl;
  }
}

void drawChristmasTree(const int n) {
  for (int part = 1; part <= n; ++ part) {
    drawPyramid(part, n - part);
  }
}


// size from 2 to 20
void drawFigureX(int size){
}

// size from 2 to 20
void drawFigureY(int size){
}

// size from 3 to 20
void drawFigureZ(int size){
}

// size from 2 to 20
void drawFigureW(int size){
}

//int main() {
//  drawTriangle(5);
//  return 0;
//}

bool isCommand(const string command,const char *mnemonic){
  return command==mnemonic;
}

//int main(){
//  drawChristmasTree(4);
//}


int main(){
  string line;
  string command;
  int value;
  cout << "START" << endl;
  while(true){
//		cin.getline(line, MAXLINE);
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

    // read next argument, one int value
    stream >> value;

    if(isCommand(command,"TR"))
    {
      drawTriangle(value);
      continue;
    }
    if(isCommand(command,"SQ"))
    {
      drawSquare(value);
      continue;
    }
    if(isCommand(command,"PY"))
    {
      drawPyramid(value);
      continue;
    }
    if(isCommand(command,"CT"))
    {
      drawChristmasTree(value);
      continue;
    }
    if(isCommand(command,"FX"))
    {
      drawFigureX(value);
      continue;
    }
    if(isCommand(command,"FY"))
    {
      drawFigureY(value);
      continue;
    }
    if(isCommand(command,"FZ"))
    {
      drawFigureZ(value);
      continue;
    }
    if(isCommand(command,"FW"))
    {
      drawFigureW(value);
      continue;
    }

    cout << "wrong argument in test: " << command << endl;
  }

}
