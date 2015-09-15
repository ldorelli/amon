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

std::vector<double> amon::InformationNetwork::lossOfAttention() {
	std::queue<int> Q;
	std::vector<double> vres;
	double res = 0.0;
	double tot = 0.0;

	std::cerr << "Calculating loss of attention indexes...\n";
	amon::ProgressBar bar(g.nodesQty(), 0.001);

	for (int i = 0; i < g.nodesQty(); ++i) {
		if (g.isDeleted(i)) continue;
		res = 0.0;
		tot = 0.0;
		for (auto e = g.neighboorsBegin(i); e != g.neighboorsEnd(i); g.nextNeighboor(e, i)) {
			int v = e->first;
			int subject = e->second;
			for (auto f = g.neighboorsBegin(v); f != g.neighboorsEnd(v); g.nextNeighboor(f, v)) {
				if (subject == f->second) res += 1.0;
				tot += 1.0;
			}
		}
		vres.push_back((tot != 0.0) ? (res/tot) : -1.0);
		bar += 1;
	}
	return vres;
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
					}
					d1 = v.size();
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