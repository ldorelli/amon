#include <graph.hpp>
#include <json.hpp>
#include <cstdio>
#include <iostream>
#include <network_models.hpp>
#include <epidemics.hpp>
#include <twitter.hpp>

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

	cerr << "Loading network " << argc[1] << endl;
	TweetLoader loader(argc[1], 1.0, 
		TweetLoader::NetworkType::FOLLOWING_NETWORK);

	// g = generator.simpleErdos(5000, 0.3);
	// printf("Edges: %d\n", g.edgesQty());
	// printf("Clustering: %.15lf\n", g.globalClusteringCoefficient());
	// printf("Bridges: %d\n", g.bridges());
	return 0;
}