
#include <graph/graph.hpp>
#include <iostream>
#include <set>
#include <algorithm>
#include <iomanip>    
#include <queue>
#include <sstream>
#include <thread>
#include <future>
#include <util/progress_bar.hpp>
#include <stack>
#include <utility>

const double amon::Graph::EPS = 1e-7;


BOOST_PYTHON_MODULE(amon_graph)
{
    class_<amon::Graph>("Graph", init<>())
        .def("load_undirected", &amon::Graph::loadFromEdgeFileUndirected)
    ;
}

amon::Graph::Graph() {
	edgesCount = 0;
	nodesCount = 0;
}


amon::Graph::Graph(int n) {
	edgesCount = nodesCount = 0;
	for (int i = 0; i < n; ++i) {
		addNode();
	}
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

void amon::Graph::addDirectedEdge (int A, int B) {
	addDirectedEdge(A, B, 1.0);
}

void amon::Graph::addUndirectedEdge(int A, int B) {
	addUndirectedEdge(A, B, 1.0);
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

int amon::Graph::outDegree(int x) {
	return adj[x].size();
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

double  amon::Graph::meanDegree (double percent) {
	std::vector <double> degs;
	for (int i = 0; i < (int)adj.size(); ++i) {
		if (validNodes[i]) {
			degs.push_back(adj[i].size());
		}
	}
	sort(degs.begin(), degs.end(), std::greater<double>());
	int qt = percent * nodesCount;
	double res = 0.0;
	for (int i = 0; i < qt; ++i) {
		res += degs[i];
	}
	return res/qt;
}

std::unordered_map<int, int> amon::Graph::bfs (int src) {
	std::queue<int> q;
	std::unordered_map<int, int> ans;
	ans[src] = 0;
	q.push(src);
	while (!q.empty()) {
		int n = q.front(); q.pop();
		for (auto& e : adj[n]) {
			int v = e.first;
			if (ans.count(v) != 0) continue;
			ans[v] = ans[n] + 1;
			q.push(v);
		}
	}
	return ans;
}

bool amon::Graph::isDeleted (int index) {
	if (index > (int) adj.size()) return false;
	return !validNodes[index];
}

std::string amon::Graph::toDot (bool isDirected) {
	
	std::stringstream ff;

	ff << ((isDirected) ? ("digraph g {\n") : ("graph g{\n"));
	for (int i = 0; i < (int) adj.size(); ++i) {
		for (auto& v : adj[i]) {
			int to = v.first;
			ff << i << ((isDirected) ? " -> " : " -- ") << to << " [ weight=\"" <<
				std::setprecision(4) << v.second << "\"]" << std::endl;
		}
	}
	ff << "}";
	return ff.str();
}

std::string amon::Graph::toDot (bool isDirected, std::vector<bool> inc) {
	std::stringstream ff;

	ff << ((isDirected) ? ("digraph g {\n") : ("graph g{\n"));

	for (int i = 0; i < (int) adj.size(); ++i) {
		if (!inc[i]) continue;
		for (auto& v : adj[i]) {
			int to = v.first;
			if (!inc[to]) continue;
			ff << i << ((isDirected) ? " -> " : " -- ") << to << " [ weight=\"" <<
				std::setprecision(4) << v.second << "\"]" << std::endl;
		}
	}
	ff << "}";
	return ff.str();
}

long double amon::Graph::mixingAssortativy () {
	long double exy = 0.0;
	long double ex_ey = 0.0;
	long double ex_ey2 = 0.0;
	long double m = 0;
	for (int i = 0; i < nodesCount; ++i) {
		for (auto &v : adj[i]) {
			int to = v.first;
			long double g1 = adj[to].size();
			long double g2 = adj[i].size();
			exy += g1*g2;
			ex_ey += 0.5*(g1 + g2);
			ex_ey2 += 0.5*(g1*g1 + g2*g2);
			m += 1.0;
		}
	}
	exy /= m;
	ex_ey /= m;
	ex_ey2 /= m;
	return (exy - ex_ey*ex_ey)/(ex_ey2 - ex_ey*ex_ey);
}


void amon::Graph::betweennessUnweighted(int x, std::vector<double>& res) {
	std::vector <double> sigma(nodesCount, 0.0), dist(nodesCount, -1);
	std::stack <int> S;
	std::vector < std::vector<int> > P (nodesCount);
	std::queue <int> Q;

	Q.push(x);	
	sigma[x] = 1.0;
	dist[x] = 0;
	while (!Q.empty()) {
		int v = Q.front(); Q.pop();
		S.push(v);
		for (auto p : adj[v]) {
			int w = p.first;
			if (dist[w] == -1) {
				dist[w] = dist[v] + 1;
				Q.push(w);
			}
			if (dist[w] == dist[v] + 1) {
				sigma[w] += sigma[v];
				P[w].push_back(v);
			}
		}
	}
	std::vector <double> delta(nodesCount);
	while (!S.empty()) {
		int w = S.top();
		for (int i = 0; i < (int)P[w].size(); ++i) {
			int v = P[w][i];
			delta[v] += (sigma[v]/sigma[w]) * (1 + delta[w]);
		}
		if (w != x) res[w] += delta[w];
		S.pop();
	}
}

std::vector<double> amon::Graph::unweightedBetweennssCentrality () {
	std::vector < std::vector <double> > res_t (NUM_THREADS, 
		std::vector<double> (nodesCount, 0.0));
	std::vector <double> res (nodesCount, 0.0);
	std::queue<int> Q;
	// Log the the percentage it is taking
	amon::ProgressBar bar(nodesCount, 0.00001);
	std::cerr << "Calculating betweenness centrality...[" << NUM_THREADS << " threads]\n";

	for (int i = 0; i < nodesCount; ++i) {
		if (!validNodes[i]) continue;
		Q.push(i);
		if (Q.size() == NUM_THREADS || i == nodesCount - 1) {
			std::vector<std::thread> v;
			while(!Q.empty()) {
				int p = Q.front();
				Q.pop();
				v.push_back(
					std::thread(&amon::Graph::betweennessUnweighted, this, p, 
						std::ref(res_t[p%NUM_THREADS])));
			}
			for (auto& t : v) t.join();
			bar += v.size();
		}
	}
	for (int i = 0; i < (int)res_t.size(); ++i) {
		for (int k = 0; k < (int)res_t[i].size(); ++k) {
			res[k] += res_t[i][k];
		}
	}
	for (auto& v : res) v /= ((nodesCount-1)*(nodesCount-2));
	return res;
}

void amon::Graph::clear() {
	edgesCount = nodesCount = 0;
	adj.clear();
	validNodes.clear();
	while(availableIndexes.size()) {
		availableIndexes.pop();
	}
}

void amon::Graph::loadFromEdgeFileUndirected(std::string file) {
	std::ios::sync_with_stdio(false);
	std::fstream f (file, std::ios::in);
	if (!f) {
		throw "Error opening file " + file;
	}
	int a, b;
	int m = 0;
	clear();
	std::list < std::pair<int, int> > l;
	while (f >> a >> b) {
		m = std::max(m, std::max(a + 1, b + 1));
		l.push_back(std::make_pair(a, b));
	}
	for (int i = 0; i < m; ++i) {
		addNode();
	}
	for (auto p : l) {
		std::cerr << "Read " << p.first << " to  " << p.second << std::endl;
		addUndirectedEdge(p.first, p.second);
	}
}
