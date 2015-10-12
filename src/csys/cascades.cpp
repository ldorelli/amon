#include <csys/cascades.hpp>
#include <algorithm>
#include <iostream>
#include <queue>

amon::CascadeModel::CascadeModel(amon::Graph g, double f, double adoptionThreshold, std::string innovatorModel) {
	bar = ProgressBar(g.nodesQty(), 0.00001);
	// This actually calls for a transpose graph
	std::random_device rd;
	std::default_random_engine generator (rd());
	std::uniform_real_distribution<double> unif(0.0, 1.0);

	this->g = g.transpose();
	for (int i = 0; i < g.nodesQty(); ++i) {
		states.push_back(false);
		thresholds.push_back(adoptionThreshold);
		if (innovatorModel == "degree") {
			susceptibleNodes.push(std::make_pair(g.outDegree(i), i));	
		} else {
			susceptibleNodes.push(std::make_pair(unif(generator), i));
		}
	}
	int tot = g.nodesQty()*f;
	for (int i = 0; i < tot; ++i) {
		int x = susceptibleNodes.top().second;
		states[x] = true;
		innovators.insert(x);
		susceptibleNodes.pop();
	}
}

bool amon::CascadeModel::step() {
	std::vector<int> putBack;
	std::random_device rd;
	std::default_random_engine generator (rd());
	std::uniform_real_distribution<double> unif(0.0, 1.0);

	while (!susceptibleNodes.empty()) {
		int x = susceptibleNodes.top().second;
		susceptibleNodes.pop();
		int num = 0, den = 0;
		int inno = 0;
		std::vector<int> par;
		for (auto it = g.adjBegin(x); it != g.adjEnd(x); g.adjNext(it, x)) {
			int v = it->first;
			if (states[v]) num++;
			if (innovators.count(v)) inno++;
			par.push_back(v);
			den++;
		}
		if (den == 0) continue;
		double ratio = (double)num/den;
		if (ratio > thresholds[x]) {
			states[x] = true;
			for (auto v : par) {
				cascades.addDirectedEdge(v, x);
			}
			if (inno == num) earlyAdopters.insert(x);
			for (auto x : putBack) {
				susceptibleNodes.push(std::make_pair(unif(generator), x));
			}
			bar += 1;
			return false;
		} else putBack.push_back(x);
	}
	return true;
}


amon::Graph amon::CascadeModel::getCascades() {
	return cascades;
}

std::unordered_set<int> amon::CascadeModel::getInnovators() {
	return innovators;
}

std::unordered_set<int> amon::CascadeModel::getEarlyAdopters() {
	return earlyAdopters;
}

boost::python::list amon::CascadeModel::getInnovators_py() {
	boost::python::list res;
	for (auto x : innovators) res.append(x);
	return res;
}

boost::python::list amon::CascadeModel::getEarlyAdopters_py() {
	boost::python::list res;
	for (auto x : earlyAdopters) res.append(x);
	return res;
}