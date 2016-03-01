#include <csys/information_spread.hpp>
#include <future>
#include <thread>
#include <algorithm>
#include <util/progress_bar.hpp>
#include <iostream>
#include <unordered_map>
#include <util/pyutil.hpp>

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
		res = 0.0;
		tot = 0.0;
		for (auto e = g.neighborsBegin(i); e != g.neighborsEnd(i); g.nextNeighboor(e, i)) {
			int v = e->first;
			int subject = e->second;
			for (auto f = g.neighborsBegin(v); f != g.neighborsEnd(v); g.nextNeighboor(f, v)) {
				if (subject == f->second) res += 1.0;
				tot += 1.0;
			}
		}
		vres.push_back((tot != 0.0) ? (res/tot) : -1.0);
		bar += 1;
	}
	return vres;
}

std::unordered_map<int, std::pair<int, int> > amon::InformationNetwork::informationDepth() {
	std::unordered_map <int, std::pair<int, int> > res;
	std::queue<int> Q;
	amon::ProgressBar bar(g.nodesQty(), 0.001);
	std::cerr << "Calculating information depth...[" << NUM_THREADS << " threads]\n";
	
	auto K = g.nodeKeys();
	int n = 0;
	for (int x : K) {
		Q.push(x);
		++n;
		if (Q.size() == NUM_THREADS or n == g.nodesQty()) {
			std::vector<int> idx;
			std::vector<std::future<std::pair<int, int> > > futures;
			while(!Q.empty()) {
				int cn = Q.front();
				auto fut = std::async(std::launch::async, [this, cn]() {
					std::unordered_map <int, int> v = this->g.bfs(cn);
					int depth = 0;
					for (auto p : v) {
						int d = p.second;
						depth = std::max(depth, d);
					}
					int d2 = v.size();
					return std::make_pair(d2, depth);
				});
				futures.push_back(std::move(fut));
				idx.push_back(cn);
				Q.pop();
			}
			for (int k = 0; k < futures.size(); ++k) {
				res[idx[k]] = futures[k].get();			
			}
			bar += NUM_THREADS;
		}
	}
	return res;
}


boost::python::dict amon::InformationNetwork::informationDepth_py() {
	auto v = informationDepth();
	boost::python::dict res;
	for (auto x : v) {
		boost::python::dict c;
		c["size"] = x.second.first;
		c["depth"] = x.second.second;
		res[x.first] = c;
	}
	return res;
}

boost::python::list amon::InformationNetwork::lossOfAttention_py() {
	return toPythonList(lossOfAttention());
}