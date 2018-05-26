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

class List {
public:
  struct _Node {
    int key;
    Edge val;
    _Node *next;

    explicit _Node(int key);
  };

  _Node *root;

public:
  List();
  Edge& operator[] (int x);
  Edge *Find(int x);
};

List::_Node::_Node(int key) {
  this->key = key;
  val = nullEdge;
  next = nullptr;
}

List::List() {
  root = nullptr;
}

Edge &List::operator[](int x) {
  if (!root) {
    root = new _Node(x);
    return root->val;
  }

  _Node *node = root;
  while (true) {
    if (node->key == x) {
      return node->val;
    }

    _Node *next = node->next;
    if (!next) {
      node->next = new _Node(x);
      return node->next->val;
    }

    if (next->key > x) {
      node->next = new _Node(x);
      node->next = next;
      return node->val;
    }

    node = next;
  }
}

Edge *List::Find(int x) {
  if (!root) {
    return nullptr;
  }

  _Node *node = root;
  while (true) {
    if (node->key == x) {
      return &node->val;
    }

    _Node *next = node->next;
    if (!next) {
      return nullptr;
    }

    if (next->key > x) {
      return nullptr;
    }

    node = next;
  }
}

typedef List Edges;

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
  Edge *w = edges[v1].Find(v2);
  if (!w) {
    return false;
  }

  weight = *w;
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

    List::_Node *e = edges[row].root;
    while (e) {
      cout << e->key << '(' << e->val << "),";
      e = e->next;
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
