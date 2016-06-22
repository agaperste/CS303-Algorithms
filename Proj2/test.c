
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <stdbool.h>

#include "sort.h"

int long_int_compare(const void *a, const void *b);

int main (int argc, char **argv) {
  long int *a0 = NULL, *a1 = NULL, *a2 = NULL;
  long int n = -1;

  clock_t start, finish;
  double elapsed_time;

  printf("Enter the problem size: ");
  scanf("%ld", &n); // Read the size of the list from the command line.

  if (n < 0) {
    printf("No problem size specified. Say \"bye-bye\" to the nice program!\n");
    return (16);
  }

  //**********************************
  //* Initialization. 
  //*
  a0 = (long int*) malloc(n*sizeof(long int));
  a1 = (long int*) malloc(n*sizeof(long int));
  a2 = (long int*) malloc(n*sizeof(long int));

  srand(42);
  for (long int i = 0; i < n; i++) {
    a0[i] = rand() % 99;  // Generate pseudorandom long ints between 0 and 99.
  }

  // Use the standard library qsort() to check our work.
  memcpy(a1, a0, n*sizeof(long int)); // Copy the array a0 to a1.

  start = clock();
  qsort(a1, n, sizeof(long int), &long_int_compare); 
  finish = clock();
  elapsed_time = (double) (finish-start) / CLOCKS_PER_SEC;
  printf("------------------------------\n");
  printf("Library quicksort:\n");
  printf("  Elapsed time: %f\n", elapsed_time);
  printf("------------------------------\n");
  
  // Apply insertion sort.
  memcpy(a2, a0, n*sizeof(long int));

  start = clock();
  iterative_mergesort(a2, n);
  finish = clock();
  elapsed_time = (double) (finish-start) / CLOCKS_PER_SEC;
  printf("recursive_mergesort:\n");
  printf("  Elapsed time: %f\n", elapsed_time);
  printf("  Correctly sorted? %s\n", are_identical(a1, a2, n) ? "yes" : "no");

  // Clean up: free allocated memory.
  free(a0); free(a1); free(a2);

  return 0;
}

int long_int_compare (const void *a, const void *b)
{
  const long int *x = (const long int*) a;
  const long int *y = (const long int*) b;

  return (*x - *y);
}
