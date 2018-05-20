#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

#ifndef nullptr
#define nullptr NULL
#endif

using namespace std;

template <class T>
class Matrix {
  char *arr;
  int sizeX;
  T defaultValue;

public:
  Matrix(int sizeX, int sizeY);
  T& Node(int x, int y);
  bool IsDefault(int x, int y);
  bool IsDefault(T &node);
};

template<class T>
Matrix<T>::Matrix(const int sizeX, const int sizeY) {
  size_t size = sizeof(T) * sizeX * sizeY;
  
  this->sizeX = sizeX;
  this->arr = new char[size];

#define defByte 0xFF
  memset(&defaultValue, defByte, sizeof(T));
  memset(arr, defByte, size);
}

template<class T>
T &Matrix<T>::Node(int x, int y) {
  return (T&) (*(arr + ((sizeof(T) * sizeX * y) + (sizeof(T) * x))));
}

template<class T>
bool Matrix<T>::IsDefault(int x, int y) {
  return (bool) memcmp(&Node(x, y), &defaultValue, sizeof(T));
}

template<class T>
bool Matrix<T>::IsDefault(T &node) {
  return (bool) memcmp(&node, &defaultValue, sizeof(T));
}

typedef double Edge;

class Graph {
  Matrix<Edge> *matrix = nullptr;
  int vertices = 0;

public:
  void LoadGraph(int vertices, int edges);
  void InsertEdge(int v1, int v2, Edge weight);
  bool GetEdge(int v1, int v2, Edge &weight);
  void ToMatrix();
  void ToArrays();
};

void Graph::LoadGraph(const int vertices, const int edges) {
  this->vertices = vertices;
  delete matrix;
  
  matrix = new Matrix<Edge>(vertices, vertices);
  
  for (int i = 0; i < edges; ++i) {
    int v1, v2;
    Edge w;
    
    cin >> v1 >> v2 >> w;
    
    InsertEdge(v1, v2, w);
  }
}

void Graph::InsertEdge(const int v1, const int v2, const Edge weight) {
  matrix->Node(v1, v2) = matrix->Node(v1, v2) = weight;
}

bool Graph::GetEdge(const int v1, const int v2, Edge &weight) {
  weight = matrix->Node(v1, v2);
  return matrix->IsDefault(weight);
}

void Graph::ToMatrix() {
  for (int row = 0; row < vertices; ++row) {
    for (int col = 0; col < vertices; ++col) {
      if (row == col) {
        cout << "0,";
        continue;
      }
      
      Edge w = matrix->Node(row, col);
  
      if (matrix->IsDefault(w)) {
        cout << w;
      } else {
        cout << '-';
      }
      
      cout << ',';
    }
    
    cout << endl;
  }
}

void Graph::ToArrays() {
  for (int row = 0; row < vertices; ++row) {
    cout << row << ':';
    
    for (int col = 0; col < vertices; ++col) {
      Edge w = matrix->Node(row, col);
      
      if (matrix->IsDefault(w)) {
        cout << col << '(' << w << "),";
      }
    }
    
    cout << endl;
  }
}

void loadGraph(Graph &g, int n, int m){
  g.LoadGraph(n, m);
}

void insertEdge(Graph &g, int u, int v, double weight){
  g.InsertEdge(u, v, weight);
}

bool findEdge(Graph &g, int u, int v, double &weight){
  return g.GetEdge(u, v, weight);
}

void showAsMatrix(Graph &g){
  g.ToMatrix();
}

void showAsArrayOfLists(Graph &g){
  g.ToArrays();
}

bool isCommand(const string command,const char *mnemonic){
  return command==mnemonic;
}


int main(){
  string line;
  string command;
  Graph *graph;
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
    // zero-argument command
    if(isCommand(command,"SM"))
    {
      showAsMatrix(graph[currentT]);
      continue;
    }
    
    if(isCommand(command,"SA"))
    {
      showAsArrayOfLists(graph[currentT]);
      continue;
    }
    
    
    // read next argument, one int value
    stream >> value;
    
    if(isCommand(command,"LG"))
    {
      int m;
      stream >> m;
      loadGraph(graph[currentT],value,m);
      continue;
    }
    
    if(isCommand(command,"IE"))
    {
      int v;
      double w;
      stream >> v >> w;
      insertEdge(graph[currentT],value,v,w);
      continue;
    }
    
    if(isCommand(command,"FE"))
    {
      int v;
      stream >> v;
      double w;
      bool ret=findEdge(graph[currentT],value,v,w);
      
      if(ret)
        cout << w << endl;
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
      graph=new Graph[value];
      continue;
    }
    
    cout << "wrong argument in test: " << command << endl;
    return 1;
  }
}
