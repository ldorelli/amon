#include <util/fenwick.hpp>
#include <iostream>

amon::FenwickTree::FenwickTree(int n) {
	this->n = n;
	v = std::vector<int> (n, 0);
}

amon::FenwickTree::~FenwickTree() {}

void amon::FenwickTree::add(int x, int val) {
	while (x <= n) {
		v[x] += val;
		x += (x & -x);
	}
}

int amon::FenwickTree::query (int x) {
	int res = 0;
	while (x > 0) {
		res += v[x];
		x -= (x & -x);
	}
	return res;
}

