#include <util/disjoint_sets.hpp>

#include <iostream>

amon::DisjointSet::DisjointSet(int n) {
	v = std::vector<int> (n);
	for (int i = 0; i < n; ++i) v[i] = i;
}

int amon::DisjointSet::find(int x) {
	if (v[x] == x) return x;
	return v[x] = find(v[x]);
}

void amon::DisjointSet::join(int a, int b) {
	int x = find(a);
	int y = find(b);
	if (x != y) {
		v[x] = y;
	}
}