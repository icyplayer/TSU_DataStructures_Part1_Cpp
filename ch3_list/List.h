/*
 * List.h
 *
 *  Created on: 2017年4月23日
 *      Author: icyplayer
 */

#ifndef LIST_H_
#define LIST_H_

#include "ListNode.h"
namespace myimpl {

typedef int Rank;
template<typename T> class List {
private:
	int _size; Posi(T) header; Posi(T) trailer;
protected:
	void init();
	Posi(T) first() const { return header->succ; }
	Posi(T) last() const { return trailer->pred; }

	void copyNodes(Posi(T) p, int n);
	int clear();  // return old size
public:
	List();
	~List();

	T operator[](Rank r) const;  // O(n)
	Posi(T) find(T const& e, int n, Posi(T) p) const;

	Posi(T) insertAfter (Posi(T) p, T const& e);
	Posi(T) insertBefore (Posi(T) p, T const& e);
	Posi(T) insertAsLast (T const& e);

	T remove (Posi(T) p);

	int deduplicate();  // Disordered List
	int uniquify();  // Ordered List

	Posi(T) search (T const& e) const;  // Ordered list lookup
	Posi(T) search (T const& e, int n, Posi(T) p) const;  // Ordered range lookup

	void sort (Posi(T) p, int n); //列表区间排序
	void sort() { sort ( first(), _size ); } //列表整体排序
	void selectionSort (Posi(T) p, int n);
	Posi(T) selectMax(Posi(T) p, int n);
};

} /* namespace myimpl */

#endif /* LIST_H_ */
