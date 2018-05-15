#include<iostream>
#include <string>
#include <sstream>

// DSF - disjoint sets forest

using namespace std;

class Dsf {
  struct _Node {
    int Rank;
    _Node *Parent;
	
		explicit _Node();
  };
  
  int size;
  _Node *arr;

public:
	explicit Dsf(int size);
	
	void MakeSets();
	int Find(int val);
	int Parent(int val);
	void Union(int val1, int val2);

private:
#define getPtr(val) (arr + (val))
#define getVal(ptr) ((ptr) - arr)
  _Node *find(_Node *node);
};

Dsf::_Node::_Node() {
	this->Rank = 0;
	this->Parent = this;
}

Dsf::Dsf(int size) {
	this->size = size;
	this->arr = new _Node[size];
}

void Dsf::MakeSets() {
	for (int i = 0; i < size; ++i) {
		new(&arr[i]) _Node();
	}
}

int Dsf::Find(const int val) {
  return (int) getVal(find(getPtr(val)));
}

Dsf::_Node *Dsf::find(Dsf::_Node *node) {
  _Node *parent = node->Parent;
  
  if (node == parent) {
    return parent;
  }
  
  return node->Parent = find(parent);
}

int Dsf::Parent(int val) {
  return (int) getVal(getPtr(val)->Parent);
}

void Dsf::Union(int val1, int val2) {
  _Node *par1 = find(getPtr(val1));
  _Node *par2 = find(getPtr(val2));
  
  if (par1->Rank >= par2->Rank) {
    if (par1->Rank == par2->Rank) {
      ++par1->Rank;
    }
    
    par1->Parent = par2;
  } else {
    par2->Parent = par1;
  }
}

//// element of array
//struct Element{
//	int rank;
//	int parent;
//};
//
//// DSF - disjoint sets forest
//struct DSF{
//	Element *arr;
//	int size;
//};

#define DSF Dsf

void init(DSF *&dsf, int size){
  dsf = new DSF(size);
}

void makeOneElementSets(Dsf *dsf){
  dsf->MakeSets();
}


int find(DSF * dsf, int index){
  return dsf->Find(index);
}

//void link(DSF * dsf, int index1, int index2){
//}

void makeUnion(DSF * dsf, int index1, int index2){
  dsf->Union(index1, index2);
}

int parent(DSF * dsf, int index){
  return dsf->Parent(index);
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
	Dsf **dsf=NULL;
	int currentF=0;
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

		if(isCommand(command,"MO"))
		{
			makeOneElementSets(dsf[currentF]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"IN"))
		{
			init(dsf[currentF],value);
			continue;
		}


		if(isCommand(command,"FD"))
		{
			cout << find(dsf[currentF],value) << endl;
			continue;
		}

		if(isCommand(command,"PA"))
		{
			cout << parent(dsf[currentF],value) << endl;
			continue;
		}

		if(isCommand(command,"UN"))
		{
			int value2;
			stream >> value2;
			makeUnion(dsf[currentF],value,value2);
			continue;
		}


		if(isCommand(command,"CH"))
		{
			currentF=value;
			continue;
		}

		if(isCommand(command,"GO"))
		{
			dsf=new DSF*[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;

	}
	return 0;
}