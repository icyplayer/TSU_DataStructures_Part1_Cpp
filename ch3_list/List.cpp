/*
 * List.cpp
 *
 *  Created on: 2017年4月23日
 *      Author: icyplayer
 */

#include "List.h"

namespace myimpl {


template<typename T>
void List<T>::init() {
	header = new ListNode<T>();
	trailer = new ListNode<T>();
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
	_size = 0;
}

template<typename T>
void List<T>::copyNodes(Posi(T) p, int n){
	init();
	while (0 < n--)
		insertAsLast(p->data); p = p->succ;
}

template<typename T>
List<T>::List() {
	// TODO Auto-generated constructor stub
}

template<typename T>
List<T>::~List() {
	clear(); delete header; delete trailer;
}

template<typename T>
int List<T>::clear() {  // O(n)
	int oldSize = _size;
	while (0 < _size){  // NOTE: not size--
		remove(header->succ);
	}
	return oldSize;
}

template<typename T>
T List<T>::operator[](Rank r) const{
	Posi(T) p = first();
	while (0 < r--) p = p->succ; // FIXME: r-- or --r? How about r==0?
	return p->data;
}

// 0 <= n <= rank(p) < _size if called from outside
template<typename T>
Posi(T) List<T>::find(T const& e, int n, Posi(T) p) const {
	while(0 < n--)
		if (e == ((p = p->pred)->data)) return p ;
	return NULL;
}

// TODO implemented myself, need test
template<typename T>
Posi(T) List<T>::insertAfter (Posi(T) p, T const& e){
	_size++; return p->insertAsSucc(e);
}

template<typename T>
Posi(T) List<T>::insertBefore (Posi(T) p, T const& e){
	_size++; return p->insertAsPred(e);
}

template<typename T>
Posi(T) List<T>::insertAsLast (T const& e){
	return insertBefore(trailer, e);
}

template<typename T>
T List<T>::remove (Posi(T) p){
	T e = p->data;  // Save a copy of data to return
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p; _size--; return e;
}

template<typename T>
int List<T>::deduplicate(){
	if (_size < 2) return 0;
	int oldSize = _size;
	Posi(T) p = first(); Rank r = 1;
	while (trailer != (p = p->succ)){
		Posi(T) q = find(p->data, r, p); // find REAL duplications before p
		q ? remove(q) : r++;
	}
	return oldSize - _size;
}

template<typename T>
int List<T>::uniquify() {
	if (_size < 2) return 0;
	int oldSize = _size;
	Posi(T) p = first(), q;
/*	my impl
 * 	while (trailer != p){
		Posi(T) q = p->succ;
		while ((trailer != q) && (p->data == q->data)){
			Posi(T) qSucc = q->succ;
			remove(q);
			q = qSucc;
		}
		// q == trailer or p->data != q->data
		p = q;
	}
*/
	// 03C-2 impl based on example
	while (trailer != (q = p->succ))
		(p->data == q->data) ? remove(q) : p = q;
	return oldSize - _size;
}

template<typename T>
Posi(T) List<T>::search (T const& e) const{  // Ordered list lookup

}

// Ordered range lookup
template<typename T>
Posi(T) List<T>::search (T const& e, int n, Posi(T) p) const{  // return ListNode->data <= e
	while (0 <= n--) // 0<n-- or 0<= n--(according to video 03C-3)?
		if (((p = p->pred)->data) <= e) break;
	return p; // return header/p[-(n+1)]
}  // O(1) <= Θ(n) <= O(n)

// selection sort p~p[n] ListNode. p is valid and rank(p)+n <= _size
template<typename T>
void List<T>::selectionSort (Posi(T) p, int n){
	Posi(T) head = p->pred, tail = p; // selection sort range: (head, tail)
	for (int i = 0; i < n; ++i) tail = tail->succ;
	while (1 < n){
		// 03D-3: invited unnecessary delete and new. new/delete: 100 then set/judge
//		insertBefore(tail, remove(selectMax(head->succ, n)));
		// my impl 1: modify pointer
		/*
 		Posi(T) q = selectMax(head->succ, n);
		//if (tail->pred != q){  // Ref: 03D-4 3min33s
			q->pred->succ = q->succ; q->succ->pred = q->pred;
			q->pred = tail->pred; q->succ = tail;
			tail->pred->succ = q; tail->pred = q;
		//}
		*/
		// my impl 2: swap data
 		Posi(T) q = selectMax(head->succ, n);
		if (tail->pred != q){
			T M = q->data;  // If T is a class(i.e user defined class), then copy cost is high
			q->data = tail->pred->data;
			tail->pred->data = M;
		}
		tail = tail->pred; n--;
	}

}  // O(n^2)

} /* namespace myimpl */
