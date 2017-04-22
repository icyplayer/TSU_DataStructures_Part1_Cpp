/*
 * Vector.cpp
 *
 *  Created on: 2017年4月20日
 *      Author: icyplayer
 */

#include "Vector.h"

namespace myimpl {

template<typename T>
T Vector<T>::Vector(int c = DEFAULT_CAPACITY) {
	_elem = new T[_capacity = c]; // memory allocated to this vector
	_size = 0; // elements in vector
}

template<typename T>
T Vector<T>::Vector(T const * A, Rank lo, Rank hi){
	copyFrom(A, lo, hi);
}

template<typename T>
T Vector<T>::Vector(Vector<T> const& V, Rank lo, Rank hi){
	copyFrom(V._elem, lo, hi); // FIXME: protected param _elem cannot be visited from outside
}

template<typename T>
T Vector<T>::Vector(Vector<T> const& V){
	copyFrom(V._elem, 0, V._size); // FIXME: protected param _elem cannot be visited from outside
}

template<typename T>
void Vector<T>::copyFrom(T const * A, Rank lo, Rank hi){
	delete [] _elem; // Is this necessary to avoid memory leak?
	_elem = new T[_capacity = 2*(hi-lo)]; // if do more comparison on old size and new size, will it be faster?
	_size = 0;
	while (lo < hi){
		_elem[_size++] = A[lo++];
	}
}

template<typename T>
void Vector<T>::expand(){
	if (_size < _capacity){
		return;
	}
	_capacity = max(_capacity, DEFAULT_CAPACITY);
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	for(int i = 0; i < _size; ++i){
		_elem[i] = oldElem[i];
	}
	delete [] oldElem;
}


template<typename T>
void Vector<T>::shrink(){
	// TODO
	return;
}


/* sort */
template<typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
	T *A = _elem + lo;
	int lb = mi - lo; T *B = new T[lb]; // Why not use size_t?
	for (int i = 0; i < lb; ++i) B[i] = _elem[i];  // Make a copy of 1st half of vector
	int lc = hi - mi; T *C = _elem + mi;
	int j = 0, k = 0;
	// 02F-4
	/*
	for(int i=0, j=0, k=0; (j < lb) || (k < lc);){
		if ((j < lb) && ((lc < k) || B[j] <= C[k])) A[i++] = B[j++];  // C[k] not exists or B[j] <= C[k]
		if ((k < lc) && ((lb < j) || C[k] <  B[j])) A[i++] = C[k++];  // B[j] not exists or C[k] <  B[k]
	}
	*/
	// 02F-5
	// consider single border condition: B used-up first, then quit loop.
	// Elements remain in C is untouched and will not be changed.
	for(int i=0, j=0, k=0; j < lb;){
		if ((k < lc) && C[k] <  B[j]) A[i++] = C[k++];  // B[j] not exists or C[k] <  B[k]
		if ((lc < k) || B[j] <= C[k]) A[i++] = B[j++];  // C[k] not exists or B[j] <= C[k]
	}

	delete [] B;
}

template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
	if (hi - lo < 2) return;
	Rank mi = (lo+hi) >> 1;
	mergeSort(lo, mi);
	mergeSort(mi, hi);
	merge(lo, mi, hi);
}



template<typename T>
T& Vector<T>::operator[] (Rank r) const { // TODO what does "const" mean?
	return _elem[r];
}

template<typename T>
Rank Vector<T>::insert(Rank r, T e){
	expand(); // No overflow risk
	int i = _size-1, j = _size;
	while (i >= r){
		_elem[j--] = _elem[i--]; // elements from rank=r shift right
	}
	_elem[r] = e;
	_size++;
//	expand(); // Ref: video 02C-3
	return r;
}
// O(n)
template<typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
	if (lo == hi){
		return;
	}
	while (hi < _size){
		_elem[lo++] = _elem[hi++];
	}
	_size = lo;
//	shrink();//update _capacity, if necessary.
	return hi-lo; // Note: hi, lo are updated
}

template<typename T>
T Vector<T>::remove(Rank r) {
	T e = _elem[r]; // Save a copy of removed element
	remove(r, r+1);
	return e;
}

// O(n). Input-sensitive
// disordered vector
template<typename T>
Rank Vector<T>::find(T const& e ,Rank lo, Rank hi) {
	while ((lo < hi--) && (_elem[hi] != e)); // reverse lookup
	return hi; // hi<lo, find failed; o.w, hi is e's rank
}

// ordered vector
template<typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const {
	return (rand() % 2) ? // To easier the test
	   binSearch(e, lo, hi)
	 : fibSearch(e, lo, hi);
}

// Ordered vector
// Binary search: Middle point - median point
// Not input sensitive
// O(logn)
template<typename T>
static Rank Vector<T>::binSearch(T const& e, Rank lo, Rank hi) const {
	// 02D4-2, B ver.
//	while (hi-lo > 1){
//		Rank mi = (hi+lo) >> 1;
//		(e < _elem[mi]) ? hi = mi : lo = mi+1;
//	}
//	return  (e == _elem[lo]) ? lo : -1;
	// 02D4-3, C ver.
	while (hi > lo){
		Rank mi = (hi+lo) >> 1;
		(e < _elem[mi]) ? hi = mi : lo = mi+1;
	}
	return  --lo;
}

template<typename T>
Rank binSearch(T* A, T const& e, Rank lo, Rank hi) const {
	// 02D4-2, B ver.
	while (hi-lo > 1){
		Rank mi = (hi+lo) >> 1;
		(e < A[mi]) ? hi = mi : lo = mi+1;
	}
	return  (e == A[lo]) ? lo : -1;
}


// Ordered vector
// fibSearch: Middle point - golden section ratio
template<typename T>
static Rank Vector<T>::fibSearch(T const& e, Rank lo, Rank hi) const {
	using namespace toolkit;
	Fib fib(hi-lo);
	while (lo < hi){
		while (hi-lo < fib.get())
			fib.prev();  // FIXME: seems unnecessary
		Rank mi = lo + fib.get() - 1; // FIXME: lo=0, hi=9, fib=13, mi=12
		if (e < _elem[mi])
			hi = mi;
		else if (_elem[mi])
			lo = mi+1;
		else
			return mi;
	}
	return -1;  // Search failed
}

// disordered vector
template<typename T>
int Vector<T>::deduplicate(){
	Rank oldSize = _size;
	Rank i = 1; // Start from _elem[1]
	while (i < _size){
		(find(_elem[i], 0, i) < 0) ?
			i++ // No duplicate, check _elem[i]'s success
			: remove(i); // o.w, remove the duplicated element
	}
	return oldSize - _size;
}

/*
template<typename T>
int Vector<T>::uniquify(){
// NOTE: still cannot reach high efficiency
	Rank oldSize = _size;
	Rank i = 0; // Start from _elem[0]
	while (i < _size-1){
		Rank j = i+1;
		while ((j < _size) && (_elem[i] == _elem[j++]));
		remove(i+1, j);
		i++;
	}
	return oldSize - _size;
}
*/

// ordered vector
template<typename T>
int Vector<T>::uniquify(){ // CON: complicate to understand in the first instance
	Rank i = 0, j = 0;
	while (++j < _size){
		if (_elem[i] != _elem[j]){
			_elem[++i] = _elem[j];
		}
	}
	_size = ++i; // shrink();
	return j - i;
} // NOTE: remove(lo, hi) still cannot reach high efficiency

template<typename T>
int Vector<T>::disordered() const{
	int n = 0;
	for (Rank i = 1; i< _size; ++i){
		n += (_elem[i] < _elem[i-1]);
	}
	return n;
}









/* Iterator */
// Function pointer
template<typename T>
void Vector<T>::traverse(void (*visit)(T&)){
	for (Rank i = 0; i < _size; ++i){
		visit(_elem[i]);
	}
}

// Function object
template<typename T> template<typename VST>
void Vector<T>::traverse(VST& visit){
	for (Rank i = 0; i < _size; ++i){
		visit(_elem[i]);
	}
}




/* Iterating example */
template<typename T>
void Vector<T>::increase(Vector<T> &V){
	V.traverse(Increase<T>());
}

/* Iterating practices */
template<typename T>
void Vector<T>::decrease(Vector<T> &V){
	V.traverse(Decrease<T>());
}

template<typename T>
void Vector<T>::doubleOpt(Vector<T> &V){
	V.traverse(DoubleOpt<T>());
}

//template<typename T>
//void Vector<T>::sum(Vector<T> &V){
//	V.traverse(Sum<T>());
//}

} /* namespace myimpl */
