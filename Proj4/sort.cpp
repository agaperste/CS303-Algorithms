#include <string>
#include <vector>
using std::string;
using std::vector;

#define max(x,y) ((x) > (y) ? x : y)
#define min(x,y) ((x) < (y) ? x : y)

//Function prototypes
template <typename T> void merge_sort_sort (T *a, vector<T> &aux, long int lo, long int hi);
template <typename T> void merge_sort_sort (vector<T> &a, vector<T> &aux, long int lo, long int hi);
template <typename T> void merge(T *a, vector<T> &aux, long int lo, long int mid, long int hi);
template <typename T> void merge(vector<T> &a, vector<T> &aux, long int lo, long int mid, long int hi);


template <typename T> 
void recursive_mergesort (T *a, long int n) {	
	/* Declare and initialize aux[]. */
	vector<T> aux(n);
	if (n <= 0) { return; }
	/* Cannot access array element out of range. */
	merge_sort_sort(a, aux, 0, n-1);
}

template <typename T>
void recursive_mergesort (vector<T> &a) {
	/* Declare and initialize aux[]. */
	vector<T> aux(a.size());
	if (a.size() <= 0) { return; }

	merge_sort_sort(a, aux, 0, a.size()-1);

}
template <typename T>
void iterative_mergesort (T *a, long int n) {
	if (n <= 0) { 
	/* Cannot access array element out of range.*/
	return; 
	} 
	/* Declare and initialize aux[]. */
	vector<T> aux(n);
	/*  Do lg N passes of pairwise merges.
	long int aux [n];*/
	int sz, lo;
	for (sz = 1; sz < n; sz = sz + sz) /* sz: subarray size */
		for (lo = 0; lo < n-sz; lo += sz+sz) /* lo: subarray index */
			merge(a, aux, lo, lo+sz-1, min(lo+sz+sz-1, n-1));
				
}
template <typename T> void
iterative_mergesort (vector<T> &a) {
if (a.size() <= 0) { 
	/* Cannot access array element out of range.*/
	return; 
	} 
	/* Declare and initialize aux[]. */
	vector<T> aux(a.size());
	/*  Do lg N passes of pairwise merges.
	long int aux [n];*/
	int sz, lo;
	for (sz = 1; sz < a.size(); sz = sz + sz) /* sz: subarray size */
		for (lo = 0; lo < a.size()-sz; lo += sz+sz) /* lo: subarray index */
			merge(a, aux, lo, lo+sz-1, min(lo+sz+sz-1, a.size()-1));
				
}


//Vector type
template <typename T>
void merge(vector<T> &a, vector<T> &aux, long int lo, long int mid, long int hi){
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
//Vector type
template <typename T>
void merge_sort_sort (vector<T> &a, vector<T> &aux, long int lo, long int hi) {
	/* Sort a[lo..hi].*/
	if (hi <= lo) {
		return;
	}
	else {
		long int mid = lo + (hi - lo)/2;
		merge_sort_sort (a, aux, lo, mid );
		merge_sort_sort (a, aux, (mid+1), hi);
		merge(a, aux, lo, mid, hi);
	}

}
//Array type
template <typename T>
void merge_sort_sort (T *a, vector<T> &aux, long int lo, long int hi) {
	/* Sort a[lo..hi].*/
	if (hi <= lo) {
		return;
	}
	else {
		long int mid = lo + (hi - lo)/2;
		merge_sort_sort (a, aux, lo, mid );
		merge_sort_sort (a, aux, (mid+1), hi);
		merge(a, aux, lo, mid, hi);
	}
}

//Array type
template <typename T>
void merge(T *a, vector<T> &aux, long int lo, long int mid, long int hi){
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

template void recursive_mergesort<double>(double*, long int);
template void recursive_mergesort<double>(vector<double>&);
template void recursive_mergesort<string>(vector<string>&);

template void iterative_mergesort<double>(double*, long int);
template void iterative_mergesort<double>(vector<double>&);
template void iterative_mergesort<string>(vector<string>&);
