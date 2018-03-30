#include<iostream>
#include <string>
#include <sstream>
#include <algorithm>

#ifndef nullptr
#define nullptr NULL
#endif

#define BENCHMARK

using namespace std;

void swap(int &a, int &b) {
  int tmp;
  tmp = b;
  b = a;
  a = tmp;
}

#ifndef BENCHMARK
void showArray(int array[], int size){
  int *last = array + size;

  do {
    cout << *array++ << ',';
  } while (array < last);

  cout << endl;
}
#endif

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
  int key;
  int j;

  --n;

  for (int i = n - 1; i >= 0; --i) {
    key = arr[i];

    for (j = i + 1; j <= n && arr[j] < key; ++j) {
      arr[j - 1] = arr[j];
    }

    arr[j - 1] = key;

#ifndef BENCHMARK
    showArray(arr, n+1);
#endif
  }
}

void bubbleSort(int arr[], int n) {
  --n;
  
  for (int i = n; i > 0; --i) {
    for (int j = n; j > 0; --j) {
      if (arr[j] < arr [j - 1]) {
        swap(arr[j], arr[j - 1]);
      }
    }

#ifndef BENCHMARK
    showArray(arr, n + 1);
#endif
  }
}

static int *miarr;
static int misize;

void merge(int*, int, int);

// RECURSIVE
void mergeSort(int arr[], int size) {
  if (size <= 1) {
    return;
  }

  int middle = size / 2;
  int *arr2 = arr + middle;
  
  mergeSort(arr, middle);
  mergeSort(arr2, size - middle);

  merge(arr, middle, size);
  
#ifndef BENCHMARK
    showArray(miarr, misize);
#endif
}

void mergeSortIter(int arr[], int n)
{
  for (int slice = 1; slice <= n-1; slice *= 2)
  {
    for (int leftSide=0; leftSide<n-1; leftSide += 2 * slice)
    {
      int length = min(2 * slice, n - leftSide);
      
      if (slice >= length) {
        break;
      }
      
      merge(arr + leftSide, slice, length);
    }
#ifndef BENCHMARK
    showArray(arr, n);
#endif
  }
}

void merge(int *arr, int middle, int size) {
  // Copy input arrays
  int tmp[size];
  copy(arr, arr + size, tmp);
  
  int *in = tmp;
  int *in2 = tmp + middle;

  // Pointers to the cells after arrays
  int *past = in2;
  int *past2 = tmp + size;

  // Copy until one array pass
  while (in != past && in2 != past2) {
    if (*in < *in2) {
      *arr++ = *in++;
    } else {
      *arr++ = *in2++;
    }
  }

  // Copy the rest
  while (in2 != past2) {
    *arr++ = *in2++;
  }
  while (in != past) {
    *arr++ = *in++;
  }
}

#ifdef BENCHMARK
/*
#define ROUNDS 100
//typedef long double ExecutionTime;
typedef void Algorithm(int[], int);

enum Algorithms {
  AlgMergeSortIter,
  AlgMergeSortRecursive,
  AlgInsertSort,
  AlgBubbleSort,
  AlgAmount,
};

Algorithm *AlgToFunc(Algorithms algorithms) {
  switch (algorithms) {
    case AlgInsertSort:
      return insertSort;
    
    case AlgBubbleSort:
      return bubbleSort;
    
    case AlgMergeSortRecursive:
      return mergeSort;
    
    case AlgMergeSortIter:
      return mergeSortIter;
    
    case AlgAmount:
      return nullptr;
  }
}

string AlgToStr(Algorithms algorithms) {
  switch (algorithms) {
    case AlgInsertSort:
      return "InsertSort";
    
    case AlgBubbleSort:
      return "BubbleSort";
    
    case AlgMergeSortRecursive:
      return "MergeSortRecursive";
    
    case AlgMergeSortIter:
      return "MergeSortIter";
    
    case AlgAmount:
      return "Amount";
  }
  
  return string(); // Linter doesn't into switch :/
}

enum Size {
  s100,
  s1k,
  s2k,
  s5k,
  s10k,
//  s50k,
//  s100k,
      SizesAmount
};

int SizeToInt(Size size) {
  const int k = 1000;
  
  switch (size) {
    case s100:
      return 100;
    
    case s1k:
      return k;
    
    case s2k:
      return 2 * k;
    
    case s5k:
      return 5 * k;
    
    case s10k:
      return 10 * k;

//    case s50k:;
//      return 50 * k;

//    case s100k:
//      return 100 * k;
    
    case SizesAmount:
      return -1;
  }
  
  return -1; // Linter doesn't into switch :/
}

int *getArr(int size) {
  int *arr = new int[size];
  
  srand((unsigned)time(nullptr));
  
  for (int i = 0; i < size; ++i) {
    arr[i] = (rand()%100)+1;
  }
  
  return arr;
}

clock_t benchmark(const int arr[], const int size, Algorithm sort) {
  int tmp[size];
  copy(arr, arr + size, tmp);
  
  clock_t t0, t1;
  
  t0 = clock();
  sort(tmp, size);
  t1 = clock();
  
  return t1 - t0;
}

struct threadArgs {
  int *arr;
  int size;
  Algorithm *algorithm;
  clock_t *time;
};

void* thread(void *arg) {
  threadArgs *a = (threadArgs*)arg;
  
  *a->time = benchmark(a->arr, a->size, a->algorithm);
  
  pthread_exit(nullptr);
}

#define len(var) (sizeof(var) / sizeof(int))
int main() {
  int *arrs[SizesAmount][ROUNDS];
  
  // Initialize arrays of test arrays and fill them
  for (Size size = (Size)0; size < SizesAmount; size = (Size)((int)size + 1)) {
    for (int round = 0; round < ROUNDS; ++round) {
      arrs[size][round] = getArr(SizeToInt(size));
    }
  }
  
  clock_t times[AlgAmount][SizesAmount][ROUNDS];
  
  pthread_t threads[AlgAmount][SizesAmount][ROUNDS];
  pthread_attr_t threadsConf;
  
  pthread_attr_init(&threadsConf);
  pthread_attr_setdetachstate(&threadsConf, PTHREAD_CREATE_JOINABLE);
  
  // Start threads
  for (Algorithms algorithm = (Algorithms)0; algorithm < AlgAmount; algorithm = (Algorithms)((int)algorithm + 1)) {
    for (Size size = (Size)0; size < SizesAmount; size = (Size)((int)size + 1)) {
      for (int round = 0; round < ROUNDS; ++round) {
        threadArgs *arg = new threadArgs;
        arg->arr = arrs[size][round];
        arg->size = SizeToInt(size);
        arg->algorithm = AlgToFunc(algorithm);
        arg->time = &times[algorithm][size][round];
        
        while (pthread_create(&threads[algorithm][size][round], nullptr, thread, (void *)arg));
      }
    }
  }
  
  pthread_attr_destroy(&threadsConf);
  void *status;
  
  // Join to them ALL
  for (Algorithms algorithm = (Algorithms)0; algorithm < AlgAmount; algorithm = (Algorithms)((int)algorithm + 1)) {
    for (Size size = (Size) 0; size < SizesAmount; size = (Size)((int)size + 1)) {
      for (int round = 0; round < ROUNDS; ++round) {
        while (pthread_join(threads[algorithm][size][round], &status));
        cout
            << AlgToStr(algorithm) << ','
            << SizeToInt(size) << ','
            << round + 1 << ','
            << times[algorithm][size][round] << ','
            << CLOCKS_PER_SEC
            << endl;
      }
    }
  }
}
// */

#define ROUNDS 1
#define MAX_SIZE 1010

//typedef long double ExecutionTime;
typedef void Algorithm(int[], int);

enum Algorithms {
  AlgMergeSortIter,
  AlgMergeSortRecursive,
  AlgInsertSort,
  AlgBubbleSort,
  AlgAmount,
};

Algorithm *AlgToFunc(Algorithms algorithms) {
  switch (algorithms) {
    case AlgInsertSort:
      return insertSort;
    
    case AlgBubbleSort:
      return bubbleSort;
    
    case AlgMergeSortRecursive:
      return mergeSort;
    
    case AlgMergeSortIter:
      return mergeSortIter;
    
    case AlgAmount:
      return nullptr;
  }
}

string AlgToStr(Algorithms algorithms) {
  switch (algorithms) {
    case AlgInsertSort:
      return "InsertSort";
    
    case AlgBubbleSort:
      return "BubbleSort";
    
    case AlgMergeSortRecursive:
      return "MergeSortRecursive";
    
    case AlgMergeSortIter:
      return "MergeSortIter";
    
    case AlgAmount:
      return "Amount";
  }
  
  return string(); // Linter doesn't into switch :/
}

int *getArr(int size) {
  int *arr = new int[size];
  
  srand((unsigned)time(nullptr));
  
  for (int i = 0; i < size; ++i) {
    arr[i] = (rand()%100)+1;
  }
  
  return arr;
}

clock_t benchmark(const int arr[], const int size, Algorithm sort) {
  int tmp[size];
  copy(arr, arr + size, tmp);
  
  clock_t t0, t1;
  
  t0 = clock();
  sort(tmp, size);
  t1 = clock();
  
  return t1 - t0;
}

struct threadArgs {
  int *arr;
  int size;
  Algorithm *algorithm;
  clock_t *time;
};

void* thread(void *arg) {
  threadArgs *a = (threadArgs*)arg;
  
  *a->time = benchmark(a->arr, a->size, a->algorithm);
  
  pthread_exit(nullptr);
}

#define len(var) (sizeof(var) / sizeof(int))
int main() {
  int *arrs[MAX_SIZE/10][ROUNDS];
  
  // Initialize arrays of test arrays and fill them
  for (int size = 0; size < MAX_SIZE; size += 10) {
    for (int round = 0; round < ROUNDS; ++round) {
      arrs[size/10][round] = getArr(size);
    }
  }
  
  clock_t times[AlgAmount][MAX_SIZE][ROUNDS];
  
  pthread_t threads[AlgAmount][MAX_SIZE][ROUNDS];
  pthread_attr_t threadsConf;
  
  pthread_attr_init(&threadsConf);
  pthread_attr_setdetachstate(&threadsConf, PTHREAD_CREATE_JOINABLE);
  
  // Start threads
  for (Algorithms algorithm = (Algorithms)0; algorithm < AlgAmount; algorithm = (Algorithms)((int)algorithm + 1)) {
    for (int size = 0; size < MAX_SIZE; size += 10) {
      for (int round = 0; round < ROUNDS; ++round) {
        threadArgs *arg = new threadArgs;
        arg->arr = arrs[size/10][round];
        arg->size = size;
        arg->algorithm = AlgToFunc(algorithm);
        arg->time = &times[algorithm][size/10][round];
        
        while (pthread_create(&threads[algorithm][size/10][round], nullptr, thread, (void *)arg));
      }
    }
  }
  
  pthread_attr_destroy(&threadsConf);
  void *status;
  
  // Join to them ALL
  for (Algorithms algorithm = (Algorithms)0; algorithm < AlgAmount; algorithm = (Algorithms)((int)algorithm + 1)) {
    for (int size = 0; size < MAX_SIZE; size += 10) {
      for (int round = 0; round < ROUNDS; ++round) {
        while (pthread_join(threads[algorithm][size/10][round], &status));
        cout
            << AlgToStr(algorithm) << ','
            << size << ','
            << round + 1 << ','
            << times[algorithm][size/10][round] << ','
            << CLOCKS_PER_SEC
            << endl;
      }
    }
  }
}

#endif

#ifndef BENCHMARK
int * loadArray(int size){
  int *out = new int[size];

  for (int i = 0; i < size; ++i) {
    cin >> out[i];
  }

  return out;
}

bool isCommand(const string command,const char *mnemonic){
  return command==mnemonic;
}

// Test API
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
      miarr = arr;
      misize = size;
      mergeSortIter(arr,size);
      continue;
    }

    cout << "wrong argument in test: " << command << endl;
  }
  return 0;
}
#endif
