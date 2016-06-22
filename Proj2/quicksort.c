/* author: Yingzhu Zhang, Tyler Reid */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <stdbool.h>
#include "sort.h"
#define MID(x,y,z)   ((x) > (y) ? ((y) > (z) ? (y) : ((x) > (z) ? (z) : (x))) : ((y) > (z) ? ((z) > (x) ? (z) : (x)): (y)))

void median3 (long int *a, long int lo, long int hi) {
    int mid = (lo + hi)/2;
    int temp = a[lo]; a[lo] = a[mid]; a[mid] = temp; }
    

int partition(long int *a, int lo, int hi) {
  int i = lo, j = hi + 1;
    int v;
    median3(a, lo, hi);
    v = a[lo];
  while (1) {
    while (a[++i] < v) {
      if (i == hi) {
  break; } }
    while (v < a[--j]) {
      if (j == lo) {
  break; } }
    if (i >= j ) {
      break; }
    int temp = a[i]; a[i] = a[j]; a[j] = temp; }
  int temp = a[lo]; a[lo] = a[j]; a[j] = temp; 
  return j; }

void second_sort (long int *a, int lo, int hi) {
  if (hi <= lo) {return; }
  /* swtich to insertion sort when list being sorted is too small. */
  if (hi - lo + 1 <= 42) {
    insertion_sort(a+lo, hi-lo+1);}
  else {
      int j = partition(a, lo, hi);
  second_sort(a, lo, j-1);
  second_sort(a, j+1, hi);
  }
 }
  
void quicksort (long int *a, long int n) {
  second_sort(a, 0, n -1); }
