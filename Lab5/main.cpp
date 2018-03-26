#include<iostream>
#include <string>
#include <sstream>
#include <algorithm>


#ifndef nullptr
#define nullptr NULL
#endif

#define DEBUG

using namespace std;

void swap(int &a, int &b) {
  int tmp;
  tmp = b;
  b = a;
  a = tmp;
}

void showArray(int array[], int size){
  int *last = array + size;

  do {
    cout << *array++ << ',';
  } while (array < last);

  cout << endl;
}

void insertShieeeetSort(int arr[],int n)
{
  int i,j,k,elem;
  for(i=1;i<n;i++)
  {
    j=0;
    elem=arr[i]; // i-th element will be added
    while(j<i && arr[j]<=elem)// search first greater
      j++;
    for(k=i;k>j;k--) // shift elements
      arr[k]=arr[k-1];
    arr[j]=elem;
    //showArr(arr,n);
  }
}

void insertSortSlow(int arr[], int n) {
  int tmp;
  int j;

  --n;

  for (int i = n; i >= 0; --i) {
    for (j = i; j < n && arr[j + 1] < arr[j]; ++j) {
      tmp = arr[j];
      arr[j] = arr[j + 1];
      arr[j + 1] = tmp;
    }
  }
}

void insertSort(int arr[], int n) {
#ifdef DEBUG
  int _a[n];
#endif

  int key;
  int j;

  --n;

  for (int i = n - 1; i >= 0; --i) {

#ifdef DEBUG
    for(int _i = 0; _i < n+1; ++_i) {
      _a[_i] = arr[_i];
    }
#endif

#ifndef DEBUG
    showArray(arr, n+1);
#endif

    key = arr[i];

    for (j = i + 1; j <= n && arr[j] < key; ++j) {
      arr[j - 1] = arr[j];
    }

    arr[j - 1] = key;
  }
}

void bubbleSort(int arr[], int n) {
  --n;

  for (int i = 0; i < n; ++i) {
    showArray(arr, n+1);
    for (int j = 0; j < n - 1; ++j) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

void merge(int*, int, int);

void mergeSortIter(int arr[], int size) {
  if (size <= 1) {
    return;
  }

  int middle = size / 2;
  int *arr2 = arr + middle;

  mergeSortIter(arr, middle);
  mergeSortIter(arr2, size - middle);

  merge(arr, middle, size);
}

void merge(int *arr, int middle, int size) {
#ifdef DEBUG
  int _a[size];
  for (int i = 0; i < size; ++i) {
    _a[i] = arr[i];
  }
#endif

  // Copy input arrays
  int *in = new int[size];
  for (int i = 0; i < size; ++ i) {
    in[i] = arr[i];
  }

  int *in2 = in + middle;

  int i = 0;
  int *past = in + middle;
  int *past2 = in2 + size - middle;

  // Copy until one array pass
  while (in != past || in2 != past2) {
    if (*in < *in2) {
      arr[i] = *in++;
    } else {
      arr[i] = *in2++;
    }

    ++i;
  }

  // Copy the rest
  if (in == past) {
    while (in2 != past2) {
      arr[i] = *in2++;
      ++i;
    }
  } else {
    while (in != past) {
      arr[i] = *in++;
      ++i;
    }
  }

//  delete[] in;
}


int * loadArray(int size){
  // TODO !!!
  return NULL;
}

bool isCommand(const string command,const char *mnemonic){
  return command==mnemonic;
}

int main() {
//  int arr[] = {6, 2, 1, 0, 4};
  int arr[] = {1, 0};

  showArray(arr, sizeof(arr)/ sizeof(int));
  mergeSortIter(arr, sizeof(arr)/ sizeof(int));
  showArray(arr, sizeof(arr)/ sizeof(int));

  return 0;
}

/*
int main(){
  string line;
  string command;
  int size=0;
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

    // read next argument, one int size
    stream >> size;

    // one-argument command
    if(isCommand(command,"HA")){
      cout << "END OF EXECUTION" << endl;
      break;
    }

    if(isCommand(command,"IS")) //*
    {
      int *arr=loadArray(size);
      showArray(arr,size);
      insertSort(arr,size);
      continue;
    }

    if(isCommand(command,"BS")) //*
    {
      int *arr=loadArray(size);
      showArray(arr,size);
      bubbleSort(arr,size);
      continue;
    }

    if(isCommand(command,"MI")) //*
    {
      int *arr=loadArray(size);
      showArray(arr,size);
      mergeSortIter(arr,size);
      continue;
    }

    cout << "wrong argument in test: " << command << endl;
  }
  return 0;
}
 */
