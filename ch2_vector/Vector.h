/*
 * Vector.h
 *
 *  Created on: 2017年4月20日
 *      Author: icyplayer
 */

#ifndef VECTOR_H_
#define VECTOR_H_
#include <iostream>

using namespace std;
namespace myimpl {

typedef int Rank;

#define DEFAULT_CAPACITY 3


template<typename T> class Vector {
protected:
	Rank _size;
	int _capacity;
	T* _elem;
protected:
	void copyFrom(T const * A, Rank lo, Rank hi);
	void expand();
	void shrink();
public:
	Vector(int c);
	Vector(T const * A, Rank lo, Rank hi); // Copy from array
	Vector(Vector<T> const& V, Rank lo, Rank hi); // Copy from Vector<T> V[lo, hi)
	Vector(Vector<T> const& V); // Copy from whole Vector<T> V

	~Vector(){
		delete [] _elem;
	}

	Rank insert(Rank r, T e);
	int remove(Rank lo, Rank hi); // remove _elem[lo, hi)
	T remove(Rank r); // remove _elem[r] and return its value;

	Rank find(T const& e ,Rank lo, Rank hi); // find: disordered vector find
	Rank search(T const& e, Rank lo, Rank hi) const; // search: ordered vector find
	static Rank binSearch(T const& e, Rank lo, Rank hi) const; // search: ordered vector find
	Rank fibSearch(T const& e, Rank lo, Rank hi) const; // search: ordered vector find

	int deduplicate();
	int uniquify();
	void traverse(void (*visit)(T&)); // Function pointer

	template<typename VST>
	void traverse(VST& visit);

	T& operator[] (Rank r) const;// {return _elem[r];

	size_t size() const {return _size;}

	int disordered() const;




/* Iterating examples*/
public:
	void increase(Vector<T> &V);
	void decrease(Vector<T> &V);
	void doubleOpt(Vector<T> &V);
//	void sum(Vector<T> &V); // FIXME
protected:
	/* Lecture demo of ++(increase)
	 * Modification: define the struct inside class,
	 * where in original demo the struct is defined outside Vector<T>
	 */
	struct Increase{
		virtual void operator()(T & e){ e++; } // TODO: why virtual?
	};

	/* Iterating practices */
	struct Decrease{ // TODO: test(correctness)
		virtual void operator()(T & e){ e--; } // TODO: why virtual?
	};

	// Double operation
	struct DoubleOpt{ // TODO: test(correctness)
		 // Note: operator *= may not valid
		virtual void operator()(T & e){ e = e*2; } // TODO: why virtual?
	};

/*
	struct Sum{ // TODO
		virtual T operator()(Vector<T> const& V, Rank lo, Rank hi){ return sumOf(V, lo, hi); }
		// FIXME: use traverse-like function call
		T sumOf(Vector<T> const& V, Rank lo, Rank hi) const {
		    if (lo == hi){
		        return V[lo];
		    }
		    else{
		        Rank mi = (lo+hi) >> 1;
		        return sumOf(V, lo, mi) + sumOf(V, mi+1, hi);
		    }
		}
	};
*/

};







} /* namespace myimpl */

#endif /* VECTOR_H_ */
