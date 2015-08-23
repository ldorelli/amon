#include <graph.hpp>
#include <iostream>
#include <set>
#include <algorithm>
#include <queue>

amon::Graph::Graph() {
	edgesCount = 0;
	nodesCount = 0;
}

amon::Graph::~Graph() {
	adj.clear();
	validNodes.clear();
	while (availableIndexes.size()) availableIndexes.pop();
}

amon::Graph::Graph(int n) {
	for (int i = 0; i < n; ++i) addNode();
}


int amon::Graph::nodesQty() const {
	return nodesCount;
}

int amon::Graph::edgesQty() const {
	return edgesCount;	
}

int amon::Graph::addNode () {
	int idx;
	if (availableIndexes.size()) {
		idx = availableIndexes.front();
		availableIndexes.pop();
		validNodes[idx] = true;
		adj[idx].clear();
	} else {
		idx = adj.size();
		adj.push_back(std::list<std::pair<int, double> >());
		validNodes.push_back(true);
	}
	nodesCount++;
	return idx;
}


void amon::Graph::removeNode (int index) {
	if (index > (int) adj.size() or index < 0) return;
	adj[index].clear();
	validNodes[index] = false;
}

void amon::Graph::addDirectedEdge (int a, int b, double w) {
	if (a < 0 or a > nodesCount or !validNodes[a]) return;
	if (b < 0 or b > nodesCount or !validNodes[b]) return;
	adj[a].push_back(std::make_pair(b, w));
	this->edgesCount++;
}

void amon::Graph::addUndirectedEdge(int a, int b, double w) {
	if (a < 0 or a > nodesCount or !validNodes[a]) return;
	if (b < 0 or b > nodesCount or !validNodes[b]) return;
	adj[a].push_back( std::make_pair (b, w));
	adj[b].push_back( std::make_pair(a, w));
	this->edgesCount++;
}

std::list<std::pair<int, double> >::iterator
	amon::Graph::neighboorsBegin (int node) {
	
	if (node < 0 or node > nodesCount or !validNodes[node]) {
		throw "Invalid node index";
	}
	auto it = adj[node].begin();
	while (it != adj[node].end() and !validNodes[it->first]) {
		it = adj[node].erase(it);
	}
	return it;
}


std::list<std::pair<int, double> >::iterator
	amon::Graph::neighboorsEnd (int node) {
	
	if (node < 0 or node > nodesCount or !validNodes[node]) {
		throw "Invalid node index";
	}
	return adj[node].end();
}

void amon::Graph::nextNeighboor (
	std::list<std::pair<int, double> >::iterator &it, int node) {
	
	if (it == adj[node].end()) return;	
	
	int edge = it->first;
	if (!validNodes[edge]) {
		it = adj[node].erase(it);
	} else {
		it++;
	}
}

double amon::Graph::meanDegree () {
	return (double) edgesCount/nodesCount;
}

double amon::Graph::globalClusteringCoefficient() {
	std::vector < std::set<int> > L;
	std::vector < std::pair<int, int> > nodes;

	for (int i = 0; i < (int)adj.size(); ++i) {
		if (!validNodes[i]) continue;
		nodes.push_back( std::make_pair(i, L.size()) );
		L.push_back(std::set<int>());
		for (auto e : adj[i]) {
			L[i].insert(e.first);
		}
	}

	double triangles = 0.0, triplets = 0.0;
	for (int i = 0; i < (int)nodes.size(); ++i) {
		for (int j = i+1; j < (int)nodes.size(); ++j) {
			int ii = nodes[i].second;
			int jj = nodes[j].second;
			// They do not connect to each other
			if (!L[ii].count(jj) or !L[jj].count(ii)) continue;
			// Size of union -> triplets
			int sz = L[ii].size() + L[jj].size();
			std::vector <int> I(sz), U(sz);
			int usz = std::set_union(L[ii].begin(), L[ii].end(),
				L[jj].begin(), L[jj].end(), U.begin()) - U.begin();
			int isz = std::set_intersection(L[ii].begin(), L[ii].end(),
				L[jj].begin(), L[jj].end(), I.begin()) - I.begin();
			triangles += isz;
			triplets += usz - 2;
		}
	}
	triangles /= 3.0;
	triplets -= triangles*3.0;
	triplets /= 2.0;
	triplets += triangles;
	return triangles/triplets;
}


void amon::Graph::bridges(int p, int l, int& num, 
	std::vector<int>& dfsnum, std::vector<int>& dfslow, int& ans) {

	dfsnum[p] = dfslow[p] = num++;
	
	for (auto& e : adj[p]) {
		int v = e.first;
		if (v == l) continue;
	
		if (dfsnum[v] == 0) {
	
			bridges(v, p, num, dfsnum, dfslow, ans);	
			if (dfslow[v] > dfsnum[p]) {
				++ans;
			}
			dfslow[p] = std::min(dfslow[p], dfslow[v]);
		} else {
			dfslow[p] = std::min(dfslow[p], dfsnum[v]);
		}
	}
}


int amon::Graph::bridges () {
	int num = 1, ans = 0;
	std::vector<int> dfsnum(adj.size(), 0);
	std::vector<int> dfslow(adj.size(), 0);
	for (int i = 0; i < (int)adj.size(); ++i) {
		if (validNodes[i] and dfsnum[i] == 0) {
			bridges(i, -1, num, dfsnum, dfslow, ans);
		}
	}
	return ans;
}

