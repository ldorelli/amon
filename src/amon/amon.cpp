#include <graph.hpp>
#include <json.hpp>
#include <cstdio>
#include <iostream>
#include <network_models.hpp>
#include <epidemics.hpp>
#include <twitter.hpp>
#include <information_spread.hpp>
#include <unordered_map>

using namespace std;
using namespace amon;


int main (int argv, char* argc[]) {

	Json::Value root;
	// NetworkGenerator generator;
	// amon::Graph g = generator.undirectedSimpleErdosRenyi(5000, 0.018);
	
	// cerr << "Starting\n";
	// amon::SISModel sis(g, 0.0015, 0.01, 0);
	// for (int i = 0; i < 200; ++i) {
	// 	sis.step();
	// 	printf("%.5lf\n", sis.infectedRatio());
	// }

	TweetLoader loader(argc[1], 1.0, 
		TweetLoader::NetworkType::FOLLOWING_NETWORK);
	Graph g = loader.getSocialNetwork();
	// for (int i = 0; i < g.nodesQty(); ++i) {
	// 	cout << g.outDegree(i) << " ";
	// }


	// INFORMATION DEPTH 
	InformationNetwork in(g);
	vector< pair<int, int> > res = in.informationDepth();
	int i = 0;
	for (auto &p : res) {
		printf("%d %d\n", g.outDegree(i++), p.first);
	}
	
	// vector<double> res = in.lossOfAttention();
	// for (int i = 0; i < g.nodesQty(); ++i) {
	// 	if (res[i] != -1)
	// 		printf("%d %.4lf\n", g.outDegree(i), res[i]);
	// }


	// DRAW NETWORK
	// vector <bool> drawMe(g.nodesQty(), false);
	// for (int i = 0; i < g.nodesQty(); ++i) {
	// 	if (res[i].second > 20) {
	// 		drawMe[i] = true;
	// 		unordered_map <int, int> B = g.bfs(i);
	// 		for (auto v : B) drawMe[v.first] = true;
	// 	}
	// }
	// cout << g.toDot(true, drawMe);


	// std::cout << r << std::endl;	
	// g = generator.simpleErdos(5000, 0.3);
	// printf("Edges: %d\n", g.edgesQty());
	// printf("Clustering: %.15lf\n", g.globalClusteringCoefficient());
	// printf("Bridges: %d\n", g.bridges());
	return 0;
}