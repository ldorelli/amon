#include <network_models.hpp>
#include <fenwick.hpp>
#include <iostream>

amon::NetworkGenerator::NetworkGenerator() {
	gen = std::mt19937(rd());
}

amon::NetworkGenerator::NetworkGenerator(int seed) {
	gen = std::mt19937(seed);
}

amon::NetworkGenerator::~NetworkGenerator() {}

amon::Graph amon::NetworkGenerator::directedErdosRenyi(int n, double p) {
	// double p = 
	amon::Graph g(n);

	std::binomial_distribution<long long> 
		binomial((long long) n*n, (long double) p);
	long long ecount = binomial(gen);
	long long totEdges = n*n;

	amon::FenwickTree bit (n * n);

	totEdges -= n;
	for (int i = 0; i <= n; ++i) {
		bit.add(n*i + i + 1, 1);
	}

	for (int i = 0; i < ecount; ++i) {
		std::uniform_int_distribution<long long> sample(0, totEdges-1);
		int K = sample(gen);
		// Need to find the K-tht
		int lo = 1, hi = totEdges;
		while (lo != hi) {
			int mi = (lo + hi)/2;
			// Maybe a sparse tree would be more useful (could do large graphs)
			int kk = mi + 1 - bit.query(mi);
			if (kk < K) lo = mi + 1;
			else hi = mi;
		}
		// Remove this edge from possible edges
		bit.add(hi, 1);
		// Add edge to graph
		--hi;
		int v1 = hi/n;
		int v2 = hi%n;
		g.addDirectedEdge(v1, v2, 1);
		totEdges--;
	}

	return g;
}

amon::Graph amon::NetworkGenerator::undirectedErdosRenyi(int n, double p) {
	// double p = 
	amon::Graph g(n);

	std::binomial_distribution<long long> 
		binomial((long long) n*n, (long double) p);
	long long ecount = binomial(gen);
	long long totEdges = n*n;

	amon::FenwickTree bit (n * n);

	totEdges -= n;
	for (int i = 0; i <= n; ++i) {
		bit.add(n*i + i + 1, 1);
	}

	for (int i = 0; i < ecount; ++i) {
		std::uniform_int_distribution<long long> sample(0, totEdges-1);
		int K = sample(gen);
		// Need to find the K-tht
		int lo = 1, hi = totEdges;
		while (lo != hi) {
			int mi = (lo + hi)/2;
			// Maybe a sparse tree would be more useful (could do large graphs)
			int kk = mi + 1 - bit.query(mi);
			if (kk < K) lo = mi + 1;
			else hi = mi;
		}
		// Remove this edge from possible edges
		bit.add(hi, 1);
		// Add edge to graph
		--hi;
		int v1 = hi/n;
		int v2 = hi%n;
		bit.add(v2*n + v1, 1);
		g.addUndirectedEdge(v1, v2, 1);
		totEdges -= 2;
	}

	return g;
}



amon::Graph amon::NetworkGenerator::directedSimpleErdosRenyi (int n, double p) {
	amon::Graph g(n);

	std::uniform_real_distribution<double> sample(0, 1);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (j == i) continue;
			double P = sample(gen);
			if (P <= p) g.addDirectedEdge(i, j, 1);
		}
	}
	return g;
}

amon::Graph amon::NetworkGenerator::undirectedSimpleErdosRenyi (int n, double p) {
	amon::Graph g(n);

	std::uniform_real_distribution<double> sample(0, 1);
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			double P = sample(gen);
			if (P <= p) g.addUndirectedEdge(i, j, 1);
		}
	}
	return g;
}