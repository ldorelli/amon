#include <graph.hpp>

amon::Graph::Graph() {
}

amon::Graph::~Graph() {
	adj.clear();
	validNodes.clear();
	while (availableIndexes.size()) availableIndexes.pop();
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