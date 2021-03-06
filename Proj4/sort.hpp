
// Function prototypes for the publicly accessible functions.
// DO NOT MODIFY THIS FILE!!!

#if !defined(__SORT_HPP_CS303)
#define __SORT_HPP_CS303

#include <vector>
using std::vector;

// Provided for you...
template <typename T> void insertion_sort (T *a, long int n);
template <typename T> void insertion_sort (vector<T> &a);
template <typename T> bool are_identical(T *a, T *b, long int n);
template <typename T> bool are_identical(vector<T> &a, vector<T> &b);

// For you to implement...
template <typename T> void recursive_mergesort (T *a, long int n);
template <typename T> void recursive_mergesort (vector<T> &a);
template <typename T> void iterative_mergesort (T *a, long int n);
template <typename T> void iterative_mergesort (vector<T> &a);
#endif
