/*
 * Fib.h
 *
 *  Created on: 2017年4月21日
 *      Author: icyplayer
 *
 *         Ref: https://dsa.cs.tsinghua.edu.cn/~deng/ds/src_link/fibonacci/fib.h.htm
 */

#ifndef FIB_H_
#define FIB_H_


namespace toolkit {

class Fib {
private:
	// Numeric overflow of int is easy to occur.
	int f, g;  // f = fib(k - 1), g = fib(k).

public:
	Fib(int n) { // Member of fibonacci >= n
		f = 1, g = 0;  // fib(-1), fib(0)
		while (g < n)  // O(log_phi(n))
			next();
	}

	int get() const { return g;}
	int next() { g += f; f = g-f; return g; }
	int prev() { f = g-f; g -= f; return g; }
};


}  /* namespace toolkit */


#endif /* FIB_H_ */
