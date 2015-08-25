#include <graph.hpp>
#include <json.hpp>
#include <cstdio>
#include <iostream>
#include <network_models.hpp>

using namespace std;
using namespace amon;


int main (void) {

	Json::Value root;
	// for (int i = 0; i < 10; ++i)
	// 	g.addNode();

	// g.addUndirectedEdge(0, 1, 1);
	// g.addUndirectedEdge(1, 2, 1);
	// g.addUndirectedEdge(0, 2, 1);
	// g.addUndirectedEdge(2, 4, 1);
	// g.addUndirectedEdge(4, 5, 1);
	// g.addUndirectedEdge(3, 8, 1);
	// g.addUndirectedEdge(8, 9, 1);

	int sz = 0;
	for (int i = 0; i < 30; ++i) {
		NetworkGenerator generator;
		amon::Graph g = generator.undirectedErdosRenyi(5000, 0.002);
		sz += g.edgesQty();
		printf("Edges: %d\n", g.edgesQty());
		// printf("Clustering: %.15lf\n", g.globalClusteringCoefficient());
	}
	printf("%d\n", sz/30);

	// g = generator.simpleErdos(5000, 0.3);
	// printf("Edges: %d\n", g.edgesQty());
	// printf("Clustering: %.15lf\n", g.globalClusteringCoefficient());
	// printf("Bridges: %d\n", g.bridges());
	return 0;
}