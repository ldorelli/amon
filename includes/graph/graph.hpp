#include <vector>
#include <set>

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
	int nodesQty();

	/**
	 *	Returns the number of edges in the graph.
	 * 	@return The number of edges in the graph.
	 */
	int edgesQty();

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



private:
	// Adjacency list and weights
	vector< vector <int> > adj;
	vector < vector <double> > weights;
	// validNotes[i] is true if node i is active
	vector <bool> validNodes;
};
}