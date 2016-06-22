
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <string>
#include <vector>

using std::cin;  // using (namespaces): pg 35
using std::cout;
using std::cerr;
using std::endl;
using std::unique_ptr;
using std::vector;

#include "sort.hpp"

// Pretty much everything you can do in C you can do in C++, either in C-style programming or in much more complicated C++-style programming...

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

  // Error checking?  we don't need no stinkin' error checking...
  vector<double> a0(n); // vector: pg 1012

  // Fill a0 with random numbers. 
  std::mt19937 e(0); // Random number engine: Mersenne twister.
  std::uniform_real_distribution<double> u(0,100); // Convert engine output to uniform real distribution.
  for (auto &v : a0) { // Range-for: pg 233 (new in C++11)
    v = u(e);
  }

  //----------------------------------------------------------------
  // Use the vector member function sort() to check our work.

  auto a1(a0); 
    
  auto t_start = std::chrono::high_resolution_clock::now();
  std::sort(a1.begin(), a1.end());
  auto t_end = std::chrono::high_resolution_clock::now();
  cout << "Library sort:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";

  //-------------------------------
  // Apply insertion sort.

  auto a2(a0);

  t_start = std::chrono::high_resolution_clock::now();
  iterative_mergesort(a2);
  t_end = std::chrono::high_resolution_clock::now();
  cout << "Insertion sort:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";
  cout << "  Correctly sorted? " << (are_identical(a1, a2) ? "yes" : "no") << "\n";

  // No need to clean up---the vector objects will be free automatically!

  return 0;
}
