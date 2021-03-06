#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <vector>
#include <string>
#include <thread>
#include <set>
#include <queue>
#include <utility>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <fstream>
#include <boost/python.hpp>
#include <unordered_set>


namespace amon {
class Graph {

public:

	typedef std::pair<int, double> Edge;
	typedef std::unordered_map<int, int> BfsResult;
	typedef std::vector<Edge> AdjacencyList;

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
	 * @brief      { Loads a network from a file containing the edge information }
	 *
	 * @param[in]  file  { The file path to read from. }
	 */
	void loadFromEdgeFileUndirected(std::string file);

	/**
	 * @brief      { Loads a directed network from a file. }
	 *
	 * @param[in]  file  { The file path to read from. }
	 */
	void loadFromEdgeFileDirected(std::string file);

	

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
	 * @brief      { Adds a node with given integer key. }
	 *
	 * @param[in]  key   { The key of the node. }
	 */
	void addNode(int key);

	/**
	 *  Not supported.
	 *	Removes a node from the graph/
	 *	@param index Index of the node to be removed. If the node is not present
	 *	nothing will happen.
	 */
	 // void removeNode(int index);

	/**
	 * Adds a directed edge between vertices A and B with weight w.
	 * @param A The source of the edge
	 * @param B The destination of the edge
	 * @param w The weight of the edge
	 */
	void addDirectedEdge (int A, int B, double w);

	/**
	 * Adds a directed edge between vertices A and B with weight 1.
	 * @param A The source of the edge
	 * @param B The destination of the edge
	 */
	void addDirectedEdge (int A, int B);

	/**
	 *	Adds an undirected edge between vertices A and B with weight w.
	 *	@param A One of the end-points of the edge
	 * 	@param B The other endpoint
	 * @param w The weight of the edge
	 */
	void addUndirectedEdge (int A, int B, double w);


	/**
	 *	Adds an undirected edge between vertices A and B with weight 1.
	 *	@param A One of the end-points of the edge
	 * 	@param B The other endpoint
	 */
	void addUndirectedEdge (int A, int B);

	/**
	 * @brief      { Returns the outDegree of node x. }
	 *
	 * @param[in]  x     { The index of the node. }
	 *
	 * @return     { The outDegree of the node. }
	 */
	int outDegree (int x);


	/**
	 * @brief      { Returns the in degree of a node x. }
	 *
	 * @param[in]  x     { The index of the node. }
	 *
	 * @return     { The indegree of the node. }
	 */
	int inDegree(int x);

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
	 * @param node The node to get neighbors from
	 * @return An iterator to the beggining of the node list.
	 */
	std::vector<Edge>::iterator 
		neighborsBegin(int node);
	std::vector<Edge>::iterator adjBegin(int node);;

	/**
	 * Returns a const_iterator to the end of the adjacency list of node.
	 * @param node The node to get the iterator from	 
	 */
	std::vector<Edge>::iterator 
		neighborsEnd(int node);
	std::vector<Edge>::iterator adjEnd(int node);

	/**
	 * Advances the adjacency list iterator to the next neighboor. 
	 * @param iterator The iterator to advance
	 * @param node The node related to the iterator 
	 */
	void nextNeighboor (std::vector<Edge>::iterator 
		& iterator, int node);

	void adjNext (std::vector<Edge>::iterator& iterator, int node);
	

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
	 *	Breadth-First search to find minimum paths.
	 * 	@param srcs The source nodes.
	 *  @return An unordered_map containing the distances to nodes rechable from the source.
	 */
	std::unordered_map<int, int> bfs (std::vector<int> srcs);


	/**
	 * Canceled
	 * Tests if node is deleted
	 * @param index Index of the node to test
	 * @return True if given node is deleted.
	 */
	// bool isDeleted(int index);


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

	/**
	 * @brief      { Returns a vector containing the unweighted betweeness centrality for each vector. }
	 *
	 * @return     { An unordered map containing the betweeness centrality values. }
	 */
	std::unordered_map<int, double> unweightedBetweennssCentrality() ;

	/**
	 * @brief      { Returns the local clustering coefficient of a node. }
	 *
	 * @param[in]  idx   { The node index. }
	 *
	 * @return     { The local clustering coefficient of the node. }
	 */
	double localClustering(int idx);


	/**
	 * @brief 		{ Calculates the depth of the graph. Only for DAGS. }
	 * 
	 * @return  	{ The maximum depth. }
	 */
	 int getDepth(void);

	/**
	 * @brief      { Clears the graph. }
	 */
	void clear();


	/**
	 * @brief      { Calculates the component for each node. Considers the network undirected. }
	 *
	 * @return     { A hashmap from the indexes to the component number. }
	 */
	std::unordered_map<int, int> connectedComponents();

	/**
	 * @brief      { Returns a map with the eigenvector centralities for the nodes. }
	 *
	 * @param[in] numIter { Number of iterations. }
	 * @return     { The eigenvector centrality of the nodes, as a pair (key, value). }
	 */
	std::unordered_map<int, long double> eigenvectorCentrality(int numIter);


	/**
	 * @brief      { Computer the page rank for a directed graph. }
	 *
	 * @param[in]  maxIter  { The max number of iterations. }
	 * @param[in]  alpha    { The dampling factor. }
	 *
	 * @return     { description_of_the_return_value }
	 */
	std::unordered_map<int, int> pageRank(int maxIter, double alpha);

	/**
	 * @brief      { Calculates the average number of steps a random walker will stay in each node. }
	 *
	 * @param[in]  start  { Starting node. }
	 * @param[in]  steps  { Number of steps to be performed. }
	 *
	 * @return     { An unordered map with probabilities. }
	 */
	std::unordered_map<int, double> averageRandomWalkSteps(int start, int steps);

	/**
	 * @brief      { Returns a subgraph with only selected nodes. }
	 *
	 * @param[in]  keep  { The nodes to keep. }
	 *
	 * @return     { A new graph containing te subgraph. }
	 */
	amon::Graph filter(std::unordered_set<int> keep);
	 
	/*
	 * @brief      { Returns the transpose graph. }
	 *
	 * @return     { Returns the transpose graph. }
	 */
	amon::Graph transpose();

	/**
	 * @brief      { Tests if a key exists in the graph. }
	 *
	 * @param[in]  key   { The id. }
	 *
	 * @return     { True if the key exists. }
	 */
	bool hasKey (int key);

	/**
	 * @brief      { Returns an std::vector with the node keys. }
	 *
	 * @return     { std::vector containing all node keys in order. }
	 */
	std::vector<int> nodeKeys();


	/**
	 * @brief 		{ Return the proportion of bi-directional links. }
	 * @param 		{ The induced cascade. }
	 * 
	 * @return     { The proportion of bi-directional links on the network. }
	 */
	double	biDirectionalIndex (amon::Graph& g);

	/**
	 * @brief      { Returns the degree-centrality on the original network of the
	 * 				vertex with highest Dg on the cascade. }
	 *
	 * @param[in]  cascade  { The cascade as a subgraph of g. }
	 *
	 * @return     { The degree centrality in the cascade and the graph. }
	 */
	std::pair <double, double> cascadeInfluence (amon::Graph cascade);


	/**
	 * @brief      { Calculates the average tie strenght of the network by sampling. }
	 *
	 * @param[in]  <unnamed>  { parameter_description }
	 * @param[in]  <unnamed>  { parameter_description }
	 *
	 * @return     { A map of [key, value] containing all tie strenghts  }
	 */
	double averageTieStrenght ();


	/**
	 * @brief      { Returns the number of paths in a dag to a given vertex. }
	 *
	 * @return     { The number of paths ending in every vertex of the dag. The number may be rounded. }
	 */
	std::unordered_map <int, long double>  DAGPaths (); 


	boost::python::dict eigenvectorCentrality_py(int);
	boost::python::dict DAGPaths_py();
	boost::python::dict connectedComponents_py();
	boost::python::dict averageRandomWalkSteps_py(int start, int steps);
	/**
	 *    PYTHON HELPER METHODS
	 */	
	boost::python::list nodeKeys_py();
	boost::python::dict bfs_py(int); 
	boost::python::dict bfs_py(boost::python::list);
	boost::python::list adjacency_py(int);
	boost::python::dict unweightedBetweennssCentrality_py();
	boost::python::tuple cascadeInfluence_py(amon::Graph g);
	std::string toDot_py(bool, boost::python::list);
	amon::Graph filter_py(boost::python::list);
	
	int getNodeKey(int index);
	int getNodeIndex(int key);

private:
	
	int nodesCount, edgesCount;
	// Adjacency list and weights
	std::vector< std::vector <Edge> > adj;
	std::vector<int> indegree;
	std::vector<int> revKey;
	std::unordered_map<int, int> keys;

	long double dagPathsDfs (amon::Graph& g, int p, 
		std::vector<bool> &vis, std::vector<long double>& P);

	void translateNode (int &node);
 
	void ccDfs (int cur, int depth, int from, int last, 
		long long int& trips, long long int& triangles);
	
	void bridges (int p, int i, int&, 
		std::vector<int>&, std::vector<int>&, int&);
	
	unsigned int NUM_THREADS = std::thread::hardware_concurrency();

	void betweennessUnweighted (int v, std::vector<double>& res);

	int dfsDepth (int, std::vector<int>&);
};
}

#endif
