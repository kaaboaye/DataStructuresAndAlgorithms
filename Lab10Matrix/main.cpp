#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cstring>
#include <limits>

#ifndef nullptr
#define nullptr NULL
#endif

using namespace std;

typedef double Edge;
#define nullEdge numeric_limits<double>::infinity()

class Matrix {
  Edge *arr;
  int size;
  Edge defaultValue;

public:
  Matrix(int size);
  Edge& Node(int x, int y);
  bool IsDefault(int x, int y);
  bool IsDefault(Edge &node);
};

Matrix::Matrix(const int size) {
  size_t arrSize = (size_t) size * size;
  
  this->size = size;
  this->arr = new Edge[arrSize];

  defaultValue = nullEdge;

  for (int row = 0; row < size; ++row) {
    for (int col = 0; col < size; ++col) {
      if (row == col) {
        Node(row, col) = 0;
      } else {
        Node(row, col) = defaultValue;
      }
    }
  }
}

Edge &Matrix::Node(int x, int y) {
  return (Edge&) (*(arr + ((size * y) + x)));
}

bool Matrix::IsDefault(int x, int y) {
  return (bool) memcmp(&Node(x, y), &defaultValue, sizeof(Edge));
}

bool Matrix::IsDefault(Edge &node) {
  return (bool) memcmp(&node, &defaultValue, sizeof(Edge));
}

class Graph {
  Matrix *matrix;
  int vertices;

public:
  Graph();
  void LoadGraph(int vertices, int edges);
  void InsertEdge(int v1, int v2, Edge weight);
  bool GetEdge(int v1, int v2, Edge &weight);
  void ToMatrix();
  void ToArrays();
};

void Graph::LoadGraph(const int vertices, const int edges) {
  this->vertices = vertices;
  delete matrix;
  
  matrix = new Matrix(vertices);
  
  for (int i = 0; i < edges; ++i) {
    int v1, v2;
    Edge w;
    
    cin >> v1 >> v2 >> w;
    
    InsertEdge(v1, v2, w);
  }
}

void Graph::InsertEdge(const int v1, const int v2, const Edge weight) {
  matrix->Node(v1, v2) = weight;
}

bool Graph::GetEdge(const int v1, const int v2, Edge &weight) {
  weight = matrix->Node(v1, v2);
  return matrix->IsDefault(weight);
}

void Graph::ToMatrix() {
  for (int row = 0; row < vertices; ++row) {
    for (int col = 0; col < vertices; ++col) {
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
      if (row == col) {
        continue;
      }

      Edge w = matrix->Node(row, col);
      
      if (matrix->IsDefault(w)) {
        cout << col << '(' << w << "),";
      }
    }
    
    cout << endl;
  }
}

Graph::Graph() {
  matrix = nullptr;
  vertices = 0;
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
