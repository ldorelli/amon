#ifndef __NET_MODELS_H__
#define __NET_MODELS_H__

#include <graph/graph.hpp>
#include <random>


namespace amon {
class NetworkGenerator {
public:

	NetworkGenerator();
	NetworkGenerator(int seed);
	~NetworkGenerator();

	/**
	 * Random graph of Erdos-Renyi.  May generate self-loops. Directed.
	 * O(E Log^2 E)
	 * @param n The size of the graph.
	 * @param p Probability of a connection existing.
	 * @return A random graph with given parameters.
	 */
	amon::Graph directedRandomNetwork (int n, double p);

	/**
	 * Same as erdosRenyi but with an O(V^2) algotihm. Directed.
	 * @param n The size of the graph.
	 * @param p Probability of a connection existing.
	 * @return A random graph with given parameters.
	 */
	amon::Graph undirectedRandomNetwork (int n, double p);

private:
	int seed;
	bool hasSeed;
};
}


#endif