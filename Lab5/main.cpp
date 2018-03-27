#include<iostream>
#include <string>
#include <sstream>
#include <algorithm>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#include <ctime>
#endif

/* Remove if already defined */
#ifndef int64
typedef long long int64;
#endif

#ifndef uint64
typedef unsigned long long uint64;
#endif

/* Returns the amount of milliseconds elapsed since the UNIX epoch. Works on both
 * windows and linux. */

uint64 GetTime()
{
#ifdef _WIN32
  /* Windows */
 FILETIME ft;
 LARGE_INTEGER li;

 /* Get the amount of 100 nano seconds intervals elapsed since January 1, 1601 (UTC) and copy it
  * to a LARGE_INTEGER structure. */
 GetSystemTimeAsFileTime(&ft);
 li.LowPart = ft.dwLowDateTime;
 li.HighPart = ft.dwHighDateTime;

 uint64 ret = li.QuadPart;
 ret -= 116444736000000000LL; /* Convert from file time to UNIX epoch time. */
 ret /= 10000; /* From 100 nano seconds (10^-7) to 1 millisecond (10^-3) intervals */

 return ret;
#else
  /* Linux */
  struct timeval tv;

  gettimeofday(&tv, NULL);

  uint64 ret = tv.tv_usec;
  /* Convert from micro seconds (10^-6) to milliseconds (10^-3) */
  ret /= 1000;

  /* Adds the seconds (10^0) after converting them to milliseconds (10^-3) */
  ret += (tv.tv_sec * 1000);

  return ret;
#endif
}


#ifndef nullptr
#define nullptr NULL
#endif

#define FAST

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

//void insertShieeeetSort(int arr[],int n)
//{
//  int i,j,k,elem;
//  for(i=1;i<n;i++)
//  {
//    j=0;
//    elem=arr[i]; // i-th element will be added
//    while(j<i && arr[j]<=elem)// search first greater
//      j++;
//    for(k=i;k>j;k--) // shift elements
//      arr[k]=arr[k-1];
//    arr[j]=elem;
//    //showArr(arr,n);
//  }
//}
//
//void insertSortSlow(int arr[], int n) {
//  int tmp;
//  int j;
//
//  --n;
//
//  for (int i = n; i >= 0; --i) {
//    for (j = i; j < n && arr[j + 1] < arr[j]; ++j) {
//      tmp = arr[j];
//      arr[j] = arr[j + 1];
//      arr[j + 1] = tmp;
//    }
//  }
//}

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

#ifndef FAST
    showArray(arr, n+1);
#endif
  }
}

void bubbleSort(int arr[], int n) {
  --n;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
      }
    }
#ifndef FAST
    showArray(arr, n+1);
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
#ifndef FAST
    showArray(miarr, misize);
#endif
}

void mergeSortIter(int arr[], int size) {
  for (int length = 2; length < size - 1; length *= 2) {
    for (int i = 0; i * length < size - 1; ++i) {
      int begin = i * length;
      int middle = length / 2;
      int end;

      if ((i + 1) * length > size) {
        end = size - i * length - 1;
      } else {
        end = length;
      }

      if (middle > end) {
        if (length * 2 > size) {
          merge(arr, length, size);
        }

        break;
      }

      merge(arr + begin, middle, end);
    }
#ifndef FAST
    showArray(miarr, misize);
#endif
  }
}

void merge(int *arr, int middle, int size) {
  // Copy input arrays
  int *in = new int[size];
  for (int i = 0; i < size; ++ i) {
    in[i] = arr[i];
  }

  int *in2 = in + middle;

  // Pointers to the cells after arrays
  int *past = in2;
  int *past2 = in2 + size - middle;

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

//  delete in;
}


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

// Benchmark

#define len(var) sizeof(var) / sizeof(int)
#define fill(var) for (int i = 0; i < len(var); ++i) { var[i] = (rand()%100)+1; }
#define show(var) showArray((var), len(var));
int main() {
  int arr100[100];
  int arr10k[10000];
  int arr100k[100000];

  srand((unsigned)time(nullptr));

  fill(arr100);
  show(arr100);
}
//*/

// Just boring main()
/*
int main() {
  int arr[] = {6, 2, 1, 0, 4};
//  int arr[] = {0,14, 1};

  showArray(arr, sizeof(arr)/ sizeof(int));
  mergeSortIter(arr, sizeof(arr)/ sizeof(int));
//  merge(arr, 2, 3);
  showArray(arr, sizeof(arr)/ sizeof(int));

  return 0;
}
//*/

// Test API
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
      miarr = arr;
      misize = size;
      mergeSortIter(arr,size);
      continue;
    }

    cout << "wrong argument in test: " << command << endl;
  }
  return 0;
}

//*/
