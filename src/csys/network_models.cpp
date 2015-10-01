#include <csys/network_models.hpp>
#include <util/fenwick.hpp>
#include <iostream>

amon::NetworkGenerator::NetworkGenerator() {
	hasSeed = false;
}

amon::NetworkGenerator::NetworkGenerator(int seed) {
	hasSeed = true;
	this->seed = seed;
}

amon::NetworkGenerator::~NetworkGenerator() {}

amon::Graph amon::NetworkGenerator::directedRandomNetwork (int n, double p) {
	std::random_device rd;
	auto gen = hasSeed ? std::mt19937(seed) : std::mt19937(rd());

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

amon::Graph amon::NetworkGenerator::undirectedRandomNetwork (int n, double p) {
	std::random_device rd;
	auto gen = hasSeed ? std::mt19937(seed) : std::mt19937(rd());
	
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