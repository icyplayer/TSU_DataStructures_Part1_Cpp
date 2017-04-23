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

template<typename T> class List {
private:
	int _size; Posi(T) header; Posi(T) trailer;
protected:

public:
	List();
	~List();
};

} /* namespace myimpl */

#endif /* LIST_H_ */
