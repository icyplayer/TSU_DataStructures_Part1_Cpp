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

// O(n)
// Input-sensitive
template<typename T>
Rank Vector<T>::find(T const& e ,Rank lo, Rank hi) {
	while ((lo < hi--) && (_elem[hi] != e)); // reverse lookup
	return hi; // hi<lo, find failed; o.w, hi is e's rank
}

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

template<typename T>
void Vector<T>::sum(Vector<T> &V){
	V.traverse(Sum<T>());
}

} /* namespace myimpl */
