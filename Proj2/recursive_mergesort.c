/* author: Yingzhu Zhang, Tyler Reid */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <assert.h>
#include <string.h>

#include "sort.h"

/***************************************************************
 * Recursive Mergesort
 */

void merge1(long int *a, long int *aux, long int lo, long int mid, long int hi){
	/* Merge a[lo..mid] with a[mid+1..hi].*/
	int i = lo, j = mid+1;

	/* Copy a[low..hi] to aux[lo..hi]. 
	memcpy(aux, a, n*sizeof(long int)); 
	allocate once and pass it down and then free */ 
	for (long int k = lo; k <= hi; k++){  
		aux[k] = a[k]; 
		}

	for (long int k = lo; k <= hi; k++) /* Merge back to a[lo..hi].*/
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


void merge_sort_sort (long int *a, long int *aux, long int lo, long int hi) {
	/* Sort a[lo..hi].*/
	if (hi <= lo) {
		return;
	}

	/* swtich to insertion sort when list being sorted is too small. */
	if (hi - lo + 1 <= 42) {
		insertion_sort(a+lo, hi-lo+1);
	}

	else {
		long int mid = lo + (hi - lo)/2;
		merge_sort_sort (a, aux, lo, mid );
		merge_sort_sort (a, aux, (mid+1), hi);
		merge1(a, aux, lo, mid, hi);
	}

}


void recursive_mergesort (long int *a, long int n) {

	/* Declare and initialize aux[]. */
	long int *aux;
	aux = (long int*) malloc(n*sizeof(long int));

	if (n <= 0) { 
	/* Cannot access array element out of range. */
		return; 
	} 

	merge_sort_sort(a, aux, 0, n-1);
	

	/* free memory for aux[]. */
	free(aux);	
}

