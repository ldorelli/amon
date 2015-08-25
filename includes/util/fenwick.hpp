#ifndef __FENWICK_HPP_
#define __FENWICK_HPP_

#include <vector>

namespace amon {

/**
 * Simple implementation of the Fenwick Tree. O(N) space needed!!
 * Operations: add(x, v): adds x to position v (logN)
 * 	query(x): query sum of elements up to x (logN)
 */
class FenwickTree {
private:
	std::vector <int> v;
	int n;

public:
	/**
	 * Constructor
	 * @param n Number of elements.
	 */
	FenwickTree(int n);

	~FenwickTree();
	
	/**
	 * Adds v to position x in the tree.
	 * @param x The position to increment
	 * @param v The value to increment
	 */
	void add(int x, int v);

	/**
	 * Queries sum of all positions up to x.
	 * @param x The position to query up to.
	 * @return The value sought.
	 */
	int query(int x);
};
}

#endif