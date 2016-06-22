/* author: Yingzhu Zhang, Tyler Reid */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <assert.h>
#include <string.h>

#include "sort.h"

#define max(x,y) ((x) > (y) ? x : y)
#define min(x,y) ((x) < (y) ? x : y)

/***************************************************************
 * Iterative Mergesort
 */

void merge(long int *a, long int *aux, long int lo, long int mid, long int hi){
	/* Merge a[lo..mid] with a[mid+1..hi].*/
	int i = lo, j = mid+1;
	long int k;

	for (k = lo; k <= hi; k++){  
		aux[k] = a[k]; 
		}
	for (k = lo; k <= hi; k++){/* Merge back to a[lo..hi].*/
		if (i > mid) {
			a[k] = aux[j++];
		}				
		else if (j > hi) {
			a[k] = aux[i++];
		}			
		else if (aux[j] < aux[i]) {
			a[k] = aux[j++];
		}	
		else {
			a[k] = aux[i++];
		}
	}						
}

void iterative_mergesort (long int *a, long int n) {
	if (n <= 0) { 
	/* Cannot access array element out of range.*/
	return; 
	} 

	/* Declare and initialize aux[]. */
	long int *aux;
	aux = (long int*) malloc(n*sizeof(long int));

	/*  Do lg N passes of pairwise merges.
	long int aux [n];*/
	int sz, lo;
	for (sz = 1; sz < n; sz = sz + sz) /* sz: subarray size */
		for (lo = 0; lo < n-sz; lo += sz+sz) /* lo: subarray index */
			merge (a, aux, lo, lo+sz-1, min(lo+sz+sz-1, n-1));
	free(aux);
				
}



