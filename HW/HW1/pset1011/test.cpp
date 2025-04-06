/** File: heapsort.cpp */
/* This implements the heap sort algorithm (in-place).
* A given arbitrary input array goes through two passes.
* 1st pass: heap construction (heapify)
* 2nd pass: successively remove the root(max) and
*           add it to the end of array
*
* The follwing outputs show how the algorithm flows.
NOTE: This implementation does not sort the first element in the array.
NOTE: N=?? k=? .... lines are outputs at the end of each sink()
Enter a word to sort: CHRISTALONE
Input String:[ CHRISTALONE ], N=11
Input  a[11]: C H R I S T A L O N E
ASCENDING:
1st pass(heapify - O(n)) begins:
   N=11 k=5 C H R I S T A L O N E
   N=11 k=4 C H R O S T A L I N E
   N=11 k=3 C H T O S R A L I N E
   N=11 k=2 C S T O N R A L I H E
   N=11 k=1 T S R O N C A L I H E
HeapOrdered: T S R O N C A L I H E
2nd pass(swap and sink - n * O(log n) begins:
   N=10 k=1 S O R L N C A E I H
   N=9 k=1 R O H L N C A E I
   N=8 k=1 O N H L I C A E
   N=7 k=1 N L H E I C A
   N=6 k=1 L I H E A C
   N=5 k=1 I E H C A
   N=4 k=1 H E A C
   N=3 k=1 E C A
   N=2 k=1 C A
   N=1 k=1 A
a[11]: A C E H I L N O R S T
*
* author: idebtor@gmail.com
*/

#include <iostream>
#include <cstring>
using namespace std;

#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif

// define a function pointer that accepts a int array, int, int as arguments
bool (*comp)(char*, int, int);

//////////// helper functions to restore the PQ invariant ///////////
bool less(char* a, int i, int j) {
	return a[i] < a[j];
}
bool more(char* a, int i, int j) {
	return a[i] > a[j];
}

void swap(char* p, int i, int j) {
	swap(p[i], p[j]);  
}

// swim up to maintain heap-ordered
void swim(char* a, int k, int N) {
	DPRINT(cout << ">swim int=" << a[k] << " @ k=" << k << " N=" << N << endl;);
	int k_saved = k;

	while (2*k_saved <= N){
		int j = 2*k_saved;
		if( j < N && ::more(a, j, j+1)) j++;
		if( !::more(a,k_saved,j)) break;
		swap(a, k_saved, j);
		k_saved = j;
	}

	cout << "   N=" << N << " k=" << k_saved << " ";
	for (int i = 1; i <= N; i++) cout << a[i] << " ";
	cout << endl;
}

// sink down to maintain heap-ordered 
void sink(char* a, int k, int N) {
	DPRINT(cout << ">sink int=" << a[k] << " @ k=" << k << " N=" << N << endl;);
	int k_saved = k;

	while (2*k_saved <= N){
		int j = 2*k_saved;
		if( j < N && ::less(a, j, j+1)) j++;
		if( !::less(a,k_saved,j)) break;
		swap(a, k_saved, j);
		k_saved = j;
	}

	cout << "   N=" << N << " k=" << k_saved << " ";
	for (int i = 1; i <= N; i++) cout << a[i] << " ";
	cout << endl;
}

// use swim() and push a node in prority queue (or a heap)
void grow(char *a, char key, int& N) {
	cout << "your code here\n";
}

// pop a node in priority queue (or a heap); use swap() and sink 
void trim(char *a, int& N) {
	cout << "your code here\n";
}

// use sink() and construct a heap structure from a CBT
void heapify(char *a, int N) {

	int k = N/2;

	while (k >= 1) {
		int j = k*2;
		if (j+1 <= N && ::less(a, j+1, j)) j = j+1;
		if (::less(a, j, k)) {
			swap(a, k, j);
			if(j*2<=N) k = j +1;
		}
		k--;
	}

}

// sort a heap using both heapify() and trim() only.
void heapsort(char* a, int N) {
	int k;
	// 1st pass: restore the max heap property
	// start 'sink' at the last internal node and go up.
	cout << "1st pass(heapify - O(n)) begins:\n";

	heapify(a, N);

	cout << "HeapOrdered: ";
	for (k = 1; k <= N; k++) cout << a[k] << " ";
	cout << endl;

	// 2nd pass: get the max out (from root while N > 1)
	cout << "2nd pass(trim: swap and sink - O(n log n) begins:\n";

	cout << "your code here\n";
}

void show(char* a, int N) {
	cout << "a[" << N << "]: ";
	for (int i = 1; i <= N; i++)
		cout << a[i] << " ";
	cout << endl;
}

// The first element(a[0]) is excluded.
int main(int argc, char* argv[]) {
    char a[] = { ' ', 'C', 'H', 'R', 'I', 'S', 'T', 'A', 'L', 'O', 'N', 'E', '\0', '\0'};
    int N = sizeof(a) / sizeof(a[0]) - 3;   // -3 because of 1st ' ' and last two '\0'.

    heapify(a, N);
    cout << a;
}
