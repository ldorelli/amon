#include <information_spread.hpp>

#include <future>
#include <thread>
#include <algorithm>
#include <progress_bar.hpp>
#include <iostream>
#include <unordered_map>

amon::InformationNetwork::InformationNetwork (amon::Graph g) {
	this->g = g;
}


std::vector< std::pair<int, int> > amon::InformationNetwork::informationDepth() {
	std::vector <std::pair<int, int> > res;
	std::queue<int> Q;

	amon::ProgressBar bar(g.nodesQty(), 0.001);

	std::cerr << "Calculating information depth\n";
	for (int i = 0; i < g.nodesQty(); ++i) {
		if (!g.isDeleted(i)) {
			Q.push(i);
		}

		if (Q.size() == NUM_THREADS or i == g.nodesQty() - 1) {

			std::vector<std::future<std::pair<int, int> > > futures;
	
			while(!Q.empty()) {
				auto fut = std::async(std::launch::async, [this, i]() {
					std::unordered_map <int, int> v = this->g.bfs(i);
					int d1 = 0.0;
					int depth = 0;
					for (auto p : v) {
						int d = p.second;
						depth = std::max(depth, d);
						if (d == 1) d1 += 1.0;
					}
					// p.set_value(std::make_pair(1.0, 1));
					return std::make_pair(d1, depth);
				});
				futures.push_back(std::move(fut));
				Q.pop();
			}
			for (auto &f : futures) res.push_back(f.get());			
			bar += NUM_THREADS;
		}
	}
	return res;
}