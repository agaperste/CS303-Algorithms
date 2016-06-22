#include <string> // The string class: pg 131
#include <vector> // The vector class: pg 1012

// The standard namespace (std::): pg 59
using std::string;
using std::vector;
using std::unique_ptr;

/***************************************************************
* Helper function
*/

template <typename T> 
void merge(T *a, T *aux, long int lo, long int mid, long int hi){
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

template <typename T> 
void merge_sort_sort (T *a, T *aux, long int lo, long int hi) {
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
		merge(a, aux, lo, mid, hi);
	}

}


/***************************************************************
* Recursive Mergesort
*/

template <typename T> 
void recursive_mergesort (T *a, long int n) {

	/* Declare and initialize aux[]. */
	long int *aux;
	aux = (long int*) malloc(n*sizeof(long int));

	if (n <= 0) { 
	/* Cannot access array element out of range. */
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

	merge_sort_sort(a, aux, 0, n-1);
	

	/* free memory for aux[]. */
	free(aux);	
}

template <typename T> 
void recursive_mergesort (vector<T> &a){

	/* Use unique_ptr to declare aux array */
	std::unique_ptr<T> aux(new T); 
 
	/* Cannot access array element out of range. */

	merge_sort_sort(a, aux, 0, n-1);
}

/***************************************************************
* Iterative Mergesort
*/

template <typename T> 
void iterative_mergesort (T *a, long int n);{
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

template <typename T> 
void iterative_mergesort (vector<T> &a);{
	if (n <= 0) { 
	/* Cannot access array element out of range.*/
	return; 
	} 

	/* Use unique_ptr to declare aux array */
	std::unique_ptr<T> aux(new T); 

	/*  Do lg N passes of pairwise merges.
	long int aux [n];*/
	int sz, lo;
	for (sz = 1; sz < n; sz = sz + sz) /* sz: subarray size */
		for (lo = 0; lo < n-sz; lo += sz+sz) /* lo: subarray index */
			merge (a, aux, lo, lo+sz-1, min(lo+sz+sz-1, n-1));	
}


/***************************************************************
* Using the templates to create functions.
*/

template bool recursive_mergesort<double>(double*, long int);
template bool recursive_mergesort<double>(vector<double>&);
template bool recursive_mergesort<string>(vector<string>&);

template bool iterative_mergesort<double>(double*, long int);
template bool iterative_mergesort<double>(vector<double>&);
template bool iterative_mergesort<string>(vector<string>&);
