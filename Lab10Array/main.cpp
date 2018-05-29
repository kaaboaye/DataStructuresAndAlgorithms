#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cstring>
#include <limits>
#include <list>
#include <algorithm>
#include <queue>
#include <map>

#ifndef nullptr
#define nullptr NULL
#endif

using namespace std;

typedef double Edge;
#define nullEdge numeric_limits<double>::infinity()

//#define USE_LIST
#ifdef USE_LIST

struct EdgesNode {
  int first;
  Edge second;
  
  explicit EdgesNode(int key);
};

EdgesNode::EdgesNode(int key) {
  this->first = key;
  second = nullEdge;
}

class Edges: public list<EdgesNode> {

public:
  iterator find(int key);
  Edge& operator[] (int x);
  bool isKey(int key);
};

Edges::iterator Edges::find(int key) {
  iterator it;
  for (it = begin(); it != end() && it->first != key; ++it) {};
  return it;
}

Edge& Edges::operator[](int x) {
  iterator it = find(x);
  if (it != end()) {
    return (insert(it, EdgesNode(x)))->second;
  } else {
    push_back(EdgesNode(x));
    return back().second;
  }
}

bool Edges::isKey(int key) {
  return find(key) != end();
}

#else
class Edges: public map<int, Edge> {
public:
  bool isKey(int key);
};

bool Edges::isKey(int key) {
  return find(key) != end();
}

#endif

class Graph {
  Edges *edges;
  int vertices;

public:
  Graph();
  void LoadGraph(int vertices, int edges);
  void InsertEdge(int v1, int v2, Edge weight);
  bool GetEdge(int v1, int v2, Edge &weight);
  void ToMatrix();
  void ToArrays();
  void BFS(int v);
  void DFS(int v);
  
private:
  void DFSWalk(int v, bool *visited);
};

Graph::Graph() {
  edges = nullptr;
  vertices = 0;
}

void Graph::LoadGraph(const int vertices, const int edges) {
  this->vertices = vertices;
  this->edges = new Edges[vertices];
  
  for (int i = 0; i < edges; ++i) {
    int v1, v2;
    Edge w;
    
    cin >> v1 >> v2 >> w;
    InsertEdge(v1, v2, w);
  }
}

void Graph::InsertEdge(const int v1, const int v2, const Edge weight) {
  edges[v1][v2] = weight;
}

bool Graph::GetEdge(int v1, int v2, Edge &weight) {
  if (edges[v1].end() == edges[v1].find(v2)) {
    return false;
  }
  weight = edges[v1].find(v2)->second;
  return true;
}

void Graph::ToMatrix() {
  for (int row = 0; row < vertices; ++row) {
    for (int col = 0; col < vertices; ++col) {
      if (row == col) {
        cout << "0,";
        continue;
      }
      
      Edge w;
      if(GetEdge(row, col, w)) {
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
    
    for (Edges::iterator it = edges[row].begin(); it != edges[row].end(); it++) {
      cout << it->first << '(' << it->second << "),";
    }
    
    cout << endl;
  }
}

void Graph::BFS(int v) {
  queue<int> q;
  bool *visited = new bool[vertices];
  
  for (int i = 0; i < vertices; ++i) {
    visited[i] = false;
  }
  
  q.push(v);
  visited[v] = true;
  
  while (!q.empty()) {
    
    v = q.front();
    cout << v << ',';
    q.pop();
    
    for (int i = 0; i < vertices; ++i) {
      if (edges[v].isKey(i) && !visited[i]) {
        visited[i] = true;
        q.push(i);
      }
    }
  }
  
  cout << endl;
}

void Graph::DFS(int v) {
  bool *visited = new bool[vertices];
  for (int i = 0; i < vertices; ++i) {
    visited[i] = false;
  }
  
  DFSWalk(v, visited);
  
  cout << endl;
}

void Graph::DFSWalk(int v, bool *visited) {
  visited[v] = true;
  cout << v << ',';
  
  for (int i = 0; i < vertices; ++i) {
    if (v != i && edges[v].isKey(i) && !visited[i]) {
      visited[i] = true;
      DFSWalk(i, visited);
    }
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
  
  
    if(isCommand(command,"BF"))
    {
      graph[currentT].BFS(value);
      continue;
    }
  
  
    if(isCommand(command,"DF"))
    {
      graph[currentT].DFS(value);
      continue;
    }
    
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
