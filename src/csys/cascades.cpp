#include <csys/cascades.hpp>
#include <util/pyutil.hpp>
#include <algorithm>
#include <iostream>
#include <queue>

amon::CascadeModel::CascadeModel(amon::Graph g) {
	this->g = g.transpose();
}

amon::CascadeModel::CascadeModel(amon::Graph g, double f, double adoptionThreshold, std::string innovatorModel) {
	bar = ProgressBar(g.nodesQty(), 0.00001);
	// This actually calls for a transpose graph
	std::random_device rd;
	std::default_random_engine generator (rd());
	std::uniform_real_distribution<double> unif(0.0, 1.0);
	// We actually use the transpose graph 
	this->g = g.transpose();
	for (int i = 0; i < g.nodesQty(); ++i) {
		states.push_back(false);
		depth.push_back(g.nodesQty() + 1);
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
		depth[x] = 0;
		innovators.insert(x);
		susceptibleNodes.pop();
	}
}

int amon::CascadeModel::reachFromInnovators() {
	int res = 0;
	for (auto x : depth) {
		if (x != g.nodesQty() + 1) 
			res = std::max(res, x);
	}
	return res;
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
				depth[x] = std::min(depth[x], depth[v] + 1);
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

std::unordered_map<int, double> amon::CascadeModel::getEstimatedThreshold() {
	return estimatedThreshold;
}

boost::python::dict amon::CascadeModel::getEstimatedThreshold_py() {
	return toPythonDict(estimatedThreshold);
}

void amon::CascadeModel::runFromRecord(std::vector<int> record) {
	states = std::vector<bool> (g.nodesQty(), false);
	depth = std::vector<int> (g.nodesQty(), g.nodesQty() + 1);
	for (auto x : record) {
		// Already affected
		if (states[x]) continue;
		// Number of innovators influencing, number of influencing
		int infi, inf, tot;
		inf = infi = tot = 0;
		for (auto it = g.adjBegin(x); it != g.adjEnd(x); g.adjNext(it, x)) {
			int p = it->first;
			if (states[p]) {
				depth[x] = std::min(depth[x], depth[p] + 1);
				inf++;
				if (innovators.count(p)) infi++;
				cascades.addDirectedEdge(p, x);
			}
			++tot;
		}
		if (inf == 0) {
			innovators.insert(x);
			depth[x] = 0;
		} else if (infi == inf) {
			earlyAdopters.insert(x);
		}
		// A 0.0 threshold means there's just not enough information
		if (tot) {
			if (inf) {
				estimatedThreshold[x] = (double) inf/tot;
			} else estimatedThreshold[x] = 1.0;
		} else estimatedThreshold[x] = 0.0;
		states[x] = true;
	}
}

void amon::CascadeModel::runFromRecord_py(boost::python::list l) {
	runFromRecord(toStdVector<int>(l));
}