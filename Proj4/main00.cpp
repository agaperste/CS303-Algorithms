
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <string>

// using and namespaces: pg 35
using std::cerr;
using std::cin;  
using std::cout;
using std::endl;
using std::unique_ptr;

#include "sort.hpp"

// Pretty much everything you can do in C you can do in C++, either in C-style programming or in a much 
// more complicated C++-style programming... 

int my_compare(const void *a, const void *b);
template <typename T> int my_compare(const void *a, const void *b); // templates: pg 419

int main (int argc, char **argv) {
  long int n = -1;

  // Prompt the user for the size of the list.
  cout << "Enter the problem size: ";   // cout: pg 36
  cin >> n;                             // cin:  pg 46

  if (n < 0) {
    cerr << "No problem size specified. Say \"bye-bye\" to the nice program!" << endl; // cerr: pg 1067; endl: pg 37
    return (16);
  }

  //----------------------
  // Initialization. 

  unique_ptr<double[]> a0; // new: pg 178; unique_ptr (new in C++11): pg 968
  double *a1, *a2;         // regular C-style pointers, including for contrast
  try {
    a0 = unique_ptr<double[]>(new double[n]); // new: pg 178; unique_ptr (new in C++11): pg 968
    a1 = new double[n];
    a2 = new double[n];
  }
  catch (const std::exception &ack) { // Catch all exceptions (e.g., if memory allocation fails).
    cerr << "Ack! caught exception: " << ack.what() << " (" << __FILE__ << ", line " << __LINE__ << ")" << endl;
    cerr << "Say bye-bye to the nice program!" << endl;
    return 16; 
  }

  // Fill a0, a1, and a2 with random numbers. 
  std::mt19937 e(0); // Random number engine: Mersenne twister.
  std::uniform_real_distribution<double> u(0,100); // Convert engine output to uniform real distribution.
  for (long int i = 0; i < n; i++) {
    a2[i] = a1[i] = a0[i] = u(e);
  }

  // Use the standard library qsort() to check our work.  As you can see, C++ involves a lot of colons...
  auto t_start = std::chrono::high_resolution_clock::now(); // auto: pg 370
  qsort(a1, n, sizeof(double), &my_compare<double>);
  auto t_end = std::chrono::high_resolution_clock::now();
  cout << "Library quicksort:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";

  //-------------------------------
  // Apply insertion sort.

  t_start = std::chrono::high_resolution_clock::now();
  insertion_sort(a2, n);
  t_end = std::chrono::high_resolution_clock::now();
  cout << "Insertion sort:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";
  cout << "  Correctly sorted? " << (are_identical(a1, a2, n) ? "yes" : "no") << "\n";

  // Clean up: free allocated memory.
  // The unique_ptr a0 is automatically freed when it passes out of scope.
  delete[] a1; delete[] a2; // delete: pg 180.  

  return 0;
}

int my_compare (const void *a, const void *b)
{
  const double *x = (const double*) a;
  const double *y = (const double*) b;

  int retcd;
  if (*x < *y) {
    retcd = -1;
  }
  else if (*x > *y) {
    retcd = +1;
  }
  else {
    retcd = 0;
  }

  return retcd;
}

template <typename T> int my_compare (const void *a, const void *b)
{
  const T *x = (const double*) a;
  const T *y = (const double*) b;

  int retcd;
  if (*x < *y) {
    retcd = -1;
  }
  else if (*x > *y) {
    retcd = +1;
  }
  else {
    retcd = 0;
  }

  return retcd;
}
