/*
 * List.h
 *
 *  Created on: 2017年4月23日
 *      Author: icyplayer
 */

#ifndef LISTNODE_H_
#define LISTNODE_H_

#include "../DataStructures/General.h"

namespace myimpl {

#define Posi(T) ListNode<T>*  // Position of ListNode

template<typename T>
struct ListNode {
	T data;
	Posi(T) pred;
	Posi(T) succ;
	ListNode() {};  // NOTE: header and tailer's constructor
	ListNode(T e, Posi(T) p = NULL, Posi(T) s = NULL)
		: data(e), pred(p), succ(s){}

	Posi(T) insertAsPred(T const& e) {
		Posi(T) x = new ListNode(e, pred, this);
		pred->succ = x; pred = x; return x;
	}

	Posi(T) insertAsSucc(T const& e) {  // TODO implemented myself, need test
		Posi(T) x = new ListNode(e, this, succ);
		succ->pred = x; succ = x; return x;
	}

};

} /* namespace myimpl */

#endif /* LISTNODE_H_ */
