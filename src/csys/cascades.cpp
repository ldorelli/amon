#include <csys/cascades.hpp>
#include <util/pyutil.hpp>
#include <algorithm>
#include <iostream>
#include <queue>

amon::CascadeModel::CascadeModel(amon::Graph g) {
	this->g = g.transpose();
}

amon::CascadeModel::CascadeModel(amon::Graph g, double hourlyRatio, int timeSkip, double adoptionThreshold) {
	// We actually use the transpose graph
	this->g = g.transpose();
	this->timeSkip = timeSkip;
	this->adoptionThreshold = adoptionThreshold;
	this->hourlyRatio = hourlyRatio;
}

void amon::CascadeModel::setStarter (int v, int t) {
	joinedNodes[v] = t;
	cascades.addNode(g.getNodeKey(v));
}

boost::python::list amon::CascadeModel::getAdoptionTimes (void) {
	std::vector <int>  adoptionTimes;
	for (auto x : joinedNodes) {
		adoptionTimes.push_back (x.second);
	}
	std::sort (adoptionTimes.begin(), adoptionTimes.end());
	return toPythonList (adoptionTimes);
}

bool amon::CascadeModel::step(int T) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, g.nodesQty()-1);

	int tot = g.nodesQty() * hourlyRatio;

	for (int i = 0; i < tot; ++i) {
		int p = dis(gen);
		if (joinedNodes.count(p)) {
			continue;
		}
		if (willJoin(p, T)) {
			cascades.addNode(g.getNodeKey(p));
			joinedNodes[p] = T;
			// Look for the most recent share to attribute from
			for (auto x = g.adjBegin(p); x != g.adjEnd(p); g.adjNext(x, p)) {
				int y = x->first;
				if (joinedNodes.count(y)) {
					if (T - joinedNodes[y] <= timeSkip) {
						cascades.addDirectedEdge (g.getNodeKey(y), g.getNodeKey(p));
					}
				}
			}
		}
	}
}

amon::Graph amon::CascadeModel::getCascades() {
	return cascades;
}

bool amon::CascadeModel::findCascadePath(int start, int node, int depth) {
	if (depth == 0) return false;
	bool ret = false;
	for (auto it = g.adjBegin(node); it != g.adjEnd(node); g.adjNext(it, node)) {
		int v = it->first;
		if (v == start) continue;
		if (states[v] or findCascadePath(start, v, depth - 1)) {
			states[v] = true;
			states[node] = true;
			cascades.addDirectedEdge(g.getNodeKey(v), g.getNodeKey(node));
			ret = true;
		}
	}
	return ret;
}

void amon::CascadeModel::runFromRecordWithPaths(std::vector<int> record, int maxSteps) {
	int n = g.nodesQty();
	states = std::vector<bool> (n, false);

	cascades = amon::Graph();

	for (auto x : record) {
		cascades.addNode(x);
		x = g.getNodeIndex(x);
		if (states[x]) {
			continue;
		}
		states[x] = true;
		findCascadePath(x, x, maxSteps);
	}
	states.resize(0);
}

void amon::CascadeModel::runFromRecordWIthPaths_py(boost::python::list l, int depth) {
	runFromRecordWithPaths(toStdVector<int>(l), depth);
}

amon::ETCascadeModel::ETCascadeModel (amon::Graph g, double hourlyRatio, int timeRelevance, double adoptionThreshold, double alpha) :
	CascadeModel (g, hourlyRatio, timeRelevance, adoptionThreshold) {
	this->alpha = alpha;
}

amon::NETCascadeModel::NETCascadeModel (amon::Graph g, double hourlyRatio, int timeRelevance, double adoptionThreshold, double alpha) :
	CascadeModel (g, hourlyRatio, timeRelevance, adoptionThreshold) {
	this->alpha = alpha;
}

// Simplest Impl
bool amon::CascadeModel::willJoin (int p, int t) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1.0);
	return dis(gen) < adoptionThreshold;
}

bool amon::ETCascadeModel::willJoin (int p, int t) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1.0);
	return dis(gen) < adoptionThreshold * exp (-alpha * (double) t);
}

bool amon::NETCascadeModel::willJoin (int p, int t) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1.0);
	int num = 0;
	int den = 0;
	for (auto x = g.adjBegin(p); x != g.adjEnd(p); g.adjNext(x, p)) {
		int y = x->first;
		if (joinedNodes.count(y)) {
			if (dis(gen) < adoptionThreshold * exp (-alpha * (double) t)) {
				return true;
			}
		}
	}
	return false;
}
