#include <graph.hpp>
#include <json.hpp>
#include <iostream>

using namespace std;
using namespace amon;


int main (void) {
	amon::Graph g;
	Json::Value root;
	for (int i = 0; i < 10; ++i)
		g.addNode();

	g.addUndirectedEdge(0, 1, 1);
	g.addUndirectedEdge(1, 2, 1);
	g.addUndirectedEdge(0, 2, 1);
	g.addUndirectedEdge(2, 4, 1);
	g.addUndirectedEdge(4, 5, 1);
	g.addUndirectedEdge(3, 8, 1);
	g.addUndirectedEdge(8, 9, 1);
	printf("%.15lf\n", g.globalClusteringCoefficient());
	printf("%d\n", g.bridges());
	return 0;
}