#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <list>

namespace amon {
class Graph {

public:
	
	/**
	 * Empty Constructor
	 */
	Graph();

	/**
	 * Creates a graph with n nodes
	 * @param n The number of initial nodes in the graph
	 */
	Graph(int n);

	~Graph();

	/**
	 * Returns the number of nodes in the graph.
	 * @return The number of nodes in the graph.
	 */
	int nodesQty() const;

	/**
	 *	Returns the number of edges in the graph.
	 * 	@return The number of edges in the graph.
	 */
	int edgesQty() const;

	/**
	 * Adds a node to the graph.
	 * @return The index of the newly created node.
	 */
	int addNode();

	/**
	 *	Removes a node from the graph/
	 *	@param index Index of the node to be removed. If the node is not present
	 *	nothing will happen.
	 */
	 void removeNode(int index);


	/**
	 * Adds a directed edge between vertices A and B with weight w.
	 * @param A The source of the edge
	 * @param B The destination of the edge
	 * @param w The weight of the edge
	 */
	void addDirectedEdge (int A, int B, double w);

	/**
	 *	Adds an undirected edge between vertices A and B with weight w.
	 *	@param A One of the end-points of the edge
	 * 	@param B The other endpoint
	 * @param w The weight of the edge
	 */
	void addUndirectedEdge (int A, int B, double w);


	/**
	 *	Calculates the mean degree of the graph
	 *  @return The mean degree of the graph
	 */
	double meanDegree ();


	/**
	 * Returns an iterator to the begining of the adjacency list of 
	 * a node. 
	 * @param node The node to get neighboors from
	 * @return An iterator to the beggining of the node list.
	 */
	std::list<std::pair<int, double> >::iterator 
		neighboorsBegin(int node);

	/**
	 * Returns a const_iterator to the end of the adjacency list of node.
	 * @param node The node to get the iterator from	 
	 */
	std::list<std::pair<int, double> >::iterator 
		neighboorsEnd(int node);


	/**
	 * Advances the adjacency list iterator to the next neighboor. 
	 * @param iterator The iterator to advance
	 * @param node The node related to the iterator 
	 */
	void nextNeighboor (std::list<std::pair<int, double> >::iterator 
		& iterator, int node);

private:
	int nodesCount, edgesCount;
	// Adjacency list and weights
	std::vector< std::list <std::pair<int, double> > > adj;
	// validNotes[i] is true if node i is active
	std::vector <bool> validNodes;
	std::queue <int> availableIndexes;
};
}