#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <vector>
#include <string>
#include <set>
#include <queue>
#include <utility>
#include <list>
#include <map>
#include <unordered_map>

namespace amon {
class Graph {

public:
	
	static const double EPS;
	/**
	 * Empty Constructor
	 */
	Graph();

	/**
	 * Creates a graph with n nodes
	 * @param n The number of initial nodes in the graph
	 */
	Graph(int n);

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
	 * @brief      { Returns the outDegree of node x. }
	 *
	 * @param[in]  x     { The index of the node. }
	 *
	 * @return     { The outDegree of the node. }
	 */
	int outDegree (int x);
	/**
	 *	Calculates the mean degree of the graph
	 *  @return The mean degree of the graph
	 */
	double meanDegree ();

	/**
	 *
	 * The clustering coefficient of the graph
	 * @return The clustering coefficient of the graph
	 */
	 double globalClusteringCoefficient();


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
	 * Count the number of bridges on the graph.
	 * @return Number of bridges 
	 */
	int bridges ();

	/**
	 * Return the mean degree of the P percent nodes 
	 * with highest degrees.
	 * @param P The desired percentage
	 * @return The mean degree. 
	 */
	double meanDegree(double P);

	/**
	 * Calculates the average distance on the graph.
	 * Not using weights.
	 * @return The average distance excluding non-connected pairs.
	 */
	double averageDistance ();

	/**
	 *	Breadth-First search to find minimum paths.
	 * 	@param src The source node.
	 *  @return An unordered_map containing the distances to nodes rechable from the source.
	 */
	std::unordered_map<int, int> bfs (int src);

	/**
	 * Advances the adjacency list iterator to the next neighboor. 
	 * @param iterator The iterator to advance
	 * @param node The node related to the iterator 
	 */
	void nextNeighboor (std::list<std::pair<int, double> >::iterator 
		& iterator, int node);


	/**
	 * Tests if node is deleted
	 * @param index Index of the node to test
	 * @return True if given node is deleted.
	 */
	bool isDeleted(int index);


	/**
	 * @brief      { Returns a .dot description of the graph. }
	 *
	 * @param isDirected True if graph is directed.
	 * @return     { A std::string containing a .dot description of the graph }
	 */
	std::string toDot (bool isDirected);

	/**
	 * @brief      { Returns a .dot description of the graph. }
	 *
	 * @param[in]  isDirected  { True if graph is directed. }
	 * @param[in]  inc         { A vector of bools that is 1 in the i-th position if the i-th node should be included. }
	 *
	 * @return     { A std::string containing a .dot description of the graph }
	 */
	std::string toDot (bool isDirected, std::vector<bool> inc);

	/**
	 * Returns the undirected Mixing Assortativity Coefficient of the graph, as proposed by Newman.
	 * @brief      { Returns the undirected Mixing Assortativity Coefficient of the graph. }
	 *
	 * @return     { The mixing assortativity of the graph. }
	 */
	long double mixingAssortativy();


private:
	int nodesCount, edgesCount;
	// Adjacency list and weights
	std::vector< std::list <std::pair<int, double> > > adj;
	std::vector <std::list<std::string> > edgeValues;
	// validNotes[i] is true if node i is active
	std::vector <bool> validNodes;
	std::queue <int> availableIndexes;

	void bridges(int p, int i, int&, 
		std::vector<int>&, std::vector<int>&, int&);
};
}

#endif