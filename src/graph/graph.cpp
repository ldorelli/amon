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
#include <util/pyutil.hpp>
#include <sstream>
#include <util/disjoint_sets.hpp>
#include <random>
#include <gmpxx.h>

const double amon::Graph::EPS = 1e-7;


amon::Graph::Graph() {
	edgesCount = 0;
	nodesCount = 0;
}


amon::Graph::Graph(int n) {
	edgesCount = nodesCount = 0;
	for (int i = 0; i < n; ++i) {
		addNode(i);
	}
}


int amon::Graph::nodesQty() const {
	return nodesCount;
}

int amon::Graph::edgesQty() const {
	return edgesCount;	
}

void amon::Graph::addNode(int key) {
	if (keys.count(key)) throw "Key already exists";
	int idx = adj.size();
	keys[key] = idx;
	adj.push_back(std::vector<std::pair<int, double> >());
	revKey.push_back(key);
	indegree.push_back(0);
	nodesCount++;
}

void amon::Graph::translateNode(int &node) {
	if (!keys.count(node)) 	throw "Invalid node";
	node = keys[node];
}

void amon::Graph::addDirectedEdge (int a, int b, double w) {
	if (!keys.count(a)) addNode(a);
	if (!keys.count(b)) addNode(b);
	translateNode(a);
	translateNode(b);
	indegree[b]++;
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
	addDirectedEdge(a, b, w);
	addDirectedEdge(b, a, w);
}

std::vector<std::pair<int, double> >::iterator
	amon::Graph::adjBegin (int node) {
		return neighboorsBegin(node);
}


std::vector<std::pair<int, double> >::iterator
	amon::Graph::adjEnd (int node) {
		return neighboorsEnd(node);
}

std::vector<std::pair<int, double> >::iterator
	amon::Graph::neighboorsBegin (int node) {
	translateNode(node);
	auto it = adj[node].begin();
	return it;
}


std::vector<std::pair<int, double> >::iterator
	amon::Graph::neighboorsEnd (int node) {
	translateNode(node);
	return adj[node].end();
}

void amon::Graph::adjNext (
	std::vector<std::pair<int, double> >::iterator &it, int node) {
	return nextNeighboor(it, node);
}

void amon::Graph::nextNeighboor (
	std::vector<std::pair<int, double> >::iterator &it, int node) {
	translateNode(node);
	if (it == adj[node].end()) return;	
	it++;
}

int amon::Graph::outDegree(int x) {
	translateNode(x);
	return adj[x].size();
}

int amon::Graph::inDegree(int x) {
	translateNode(x);
	return indegree[x];
}

double amon::Graph::meanDegree () {
	return (double) edgesCount/nodesCount;
}

void amon::Graph::ccDfs(int c, int d, int f, int l, long long int& trp, long long int& trl) {
	if (d == 2) {
		trp++;
		for (auto  x :  adj[c]) {
			if (x.first == f) trl++;	
		}
		return;
	}
	for (auto& x : adj[c]) {
		int v = x.first;
		if (v != l)  ccDfs(v, d + 1, f, c, trp, trl);
	}
}


double amon::Graph::globalClusteringCoefficient() {
	long long int trips = 0, triangles = 0;
	for (int i = 0; i < nodesCount; ++i) {
		ccDfs(i, 0, i, -1, trips, triangles);
	}
	double T1 = (double)triangles/6.0;
	double T2 = (double)trips/2.0;
	return 3.0*T1/T2;
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
		if (dfsnum[i] == 0) {
			bridges(i, -1, num, dfsnum, dfslow, ans);
		}
	}
	return ans;
}

double  amon::Graph::meanDegree (double percent) {
	std::vector <double> degs;
	for (int i = 0; i < (int)adj.size(); ++i) {
			degs.push_back(adj[i].size());
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
	translateNode(src);
	std::queue<int> q;
	std::unordered_map<int, int> dist, ans;
	dist[src] = 0;
	q.push(src);
	while (!q.empty()) {
		int n = q.front(); q.pop();
		for (auto& e : adj[n]) {
			int v = e.first;
			if (dist.count(v) != 0) continue;
			dist[v] = dist[n] + 1;
			q.push(v);
		}
	}
	for (auto x : dist) ans[revKey[x.first]] = x.second;
	return ans;
}

std::string amon::Graph::toDot (bool isDirected) {
	
	std::stringstream ff;
	ff << ((isDirected) ? ("digraph g {\n") : ("graph g{\n"));

	for (int i = 0; i < (int) adj.size(); ++i) {
		for (auto& v : adj[i]) {
			int to = v.first;
			if (to == i) continue;
			if (!isDirected and to < i) continue;
			ff << revKey[i] << ((isDirected) ? " -> " : " -- ") << revKey[to] << " [ weight=\"" <<
				std::setprecision(4) << v.second << "\"]" << std::endl;
		}
	}
	ff << "}";
	return ff.str();
}

// TODO: Fix this method
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

std::unordered_map<int, double> amon::Graph::unweightedBetweennssCentrality () {
	std::vector < std::vector <double> > res_t (NUM_THREADS, 
		std::vector<double> (nodesCount, 0.0));
	std::vector <double> res (nodesCount, 0.0);
	std::queue<int> Q;
	// Log the the percentage it is taking
	amon::ProgressBar bar(nodesCount, 0.00001);
	std::cerr << "Calculating betweenness centrality...[" << NUM_THREADS << " threads]\n";

	for (int i = 0; i < nodesCount; ++i) {
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
	std::unordered_map<int, double> ans;
	for (int i = 0; i < res.size(); ++i) ans[revKey[i]] = res[i]; 
	return ans;
}

void amon::Graph::clear() {
	edgesCount = nodesCount = 0;
	adj.clear();
}

void amon::Graph::loadFromEdgeFileDirected(std::string file) {
	std::ios::sync_with_stdio(false);
	std::fstream f (file, std::ios::in);
	if (!f) {
		throw "Error opening file " + file;
	}
	int a, b;
	clear();
	std::string s;
	std::set< std::pair<int,int> > ES;
	while (std::getline(f, s)) {
		std::stringstream ss(s);
		ss >> a >> b;
		// if (a == b) continue;
		// if (ES.count(std::make_pair(a, b)) or ES.count(std::make_pair(b, a))) continue;
		addDirectedEdge(a, b);
		// ES.insert(std::make_pair(a, b));
	}
}


void amon::Graph::loadFromEdgeFileUndirected(std::string file) {
	std::ios::sync_with_stdio(false);
	std::fstream f (file, std::ios::in);
	if (!f) {
		throw "Error opening file " + file;
	}
	int a, b;
	clear();
	std::string s;
	std::set< std::pair<int,int> > ES;
	while (std::getline(f, s)) {
		std::stringstream ss(s);
		ss >> a >> b;
		if (a == b) continue;
		if (ES.count(std::make_pair(a, b)) or ES.count(std::make_pair(b, a))) continue;
		addUndirectedEdge(a, b);
		ES.insert(std::make_pair(a, b));
	}
}

amon::Graph amon::Graph::transpose() {
	amon::Graph res(nodesCount);
	for (int i = 0; i < nodesCount; ++i) {
		for (auto it : adj[i]) {
			res.addDirectedEdge(it.first, i, it.second);
		}
	}
	return res;
}

std::vector<int> amon::Graph::nodeKeys() {
	std::vector<int> res;
	for (auto x : keys) res.push_back(x.first);
	return res;
}

boost::python::list amon::Graph::nodeKeys_py() {
	return toPythonList(nodeKeys());
}

std::unordered_map<int, int> amon::Graph::connectedComponents() {
	std::unordered_map<int, int> res;
	amon::DisjointSet ds(nodesCount);
	for (int i = 0; i < nodesCount; ++i) {
		for (auto &x : adj[i]) {
			ds.join(i, x.first);
		}
	}
	for (int i = 0; i < nodesCount; ++i) {
		res[i] = ds.find(i);
	}
	return res;
}


amon::Graph amon::Graph::filter(std::unordered_set<int> keep) {
	amon::Graph res;
	for (auto x : keep) {
		for (auto& it : adj[x]) {
			int y = it.first;
			if (keep.count(y)) res.addDirectedEdge(x, y);
		}
	}
	return res;
}

double amon::Graph::localClustering(int i) {
	translateNode(i);
	std::set<int> v;
	std::set<std::pair<int, int> > v2;
	for (auto& it : adj[i]) {
		v.insert(it.first);
	}
	int n = v.size();
	for (auto a : v) {
		for (auto& it2 : adj[a]) {
			if (it2.first == a) continue;
			if (v.count(it2.first)) 
				v2.insert(std::make_pair(a, it2.first));
		}
	}
	int res = v2.size();
	if (n*(n-1) == 0) return 0.0;
	return (double)res/(double)(n*(n-1));
}

boost::python::dict amon::Graph::connectedComponents_py() {
	return toPythonDict(connectedComponents());
}

boost::python::list amon::Graph::adjacency_py(int index) {
	boost::python::list res;
	translateNode(index);
	if (index < 0 or index > nodesCount) throw "Index out of range";
	for (auto & p : adj[index]) {
		res.append(boost::python::make_tuple(revKey[p.first], p.second));
	}
	return res;
}

std::unordered_map<int, long double> amon::Graph::eigenvectorCentrality(int numIter) {
	std::vector<long double> res[2];
	amon::ProgressBar bar(nodesQty() * numIter, 0.001);
	int c = 0;
	std::cerr << "Calculating eigenvector centrality...[" << NUM_THREADS << " threads]\n";
	for (int i = 0; i < nodesCount; ++i) res[c].push_back(1.0/(double)nodesCount), res[!c].push_back(0.0);
	for (int t = 0; t < numIter; ++t) {
		std::fill(res[!c].begin(), res[!c].end(), 0);
		long double ss = 0.0;
		for (int i = 0; i < nodesCount; ++i) {
			for (auto &p : this->adj[i]) {
				res[!c][i] += res[c][p.first];
			}	
			ss += res[!c][i];
			bar +=  1;
		}
		c = !c;	
		for (auto& p : res[c]) p /= ss;
	}

	std::unordered_map<int, long double> ans;
	for (int i = 0; i < res[c].size(); ++i) {
		ans[revKey[i]] = res[c][i];
	}
	std::cerr << "Done\n";
	return ans;
}

std::unordered_map<int, double> amon::Graph::averageRandomWalkSteps(int start, int steps) {
	translateNode(start);
	std::vector <int> count (nodesCount);
	std::unordered_map <int, double> res;
	std::random_device rd;
    std::mt19937 gen(rd());
    int curr = start;
    count[start]++;
    for (int t = 0; t < steps; ++t) {
    	std::uniform_int_distribution<> dis(0, adj[curr].size()-1);
    	int next = adj[curr][dis(gen)].first;
    	count[next]++;
    }
    for (int i = 0; i < nodesCount; ++i)
    	res[revKey[i]] = (double) count[i]/steps;
   	return res;
}

boost::python::dict amon::Graph::averageRandomWalkSteps_py(int start, int steps) {
	return toPythonDict(averageRandomWalkSteps(start, steps));
}


boost::python::dict amon::Graph::eigenvectorCentrality_py(int numIter) {
	return toPythonDict(eigenvectorCentrality(numIter));
}


std::string amon::Graph::toDot_py (bool isDirected, boost::python::list inc) {
	return toDot(isDirected, toStdVector<bool>(inc));
}

boost::python::dict amon::Graph::bfs_py(int src) {
	return toPythonDict(bfs(src));
}


amon::Graph amon::Graph::filter_py(boost::python::list l) {
	return filter(toStdSet <int> (l));
}

boost::python::dict amon::Graph::unweightedBetweennssCentrality_py() {
	return toPythonDict(unweightedBetweennssCentrality());
}

