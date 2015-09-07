#ifndef __INFORMATION_SPREAD_H__
#define __INFORMATION_SPREAD_H__

#include <vector>
#include <graph.hpp>
#include <thread>


namespace amon {
/**
 * @brief      { Provides analysis on networks that represent information spread from people to people. }
 */
class InformationNetwork {
public:
	/**
	 * Initializes the class with given network. Nodes should be users and connections should observe
	 * the flow of information from one user to another.
	 *
	 * @brief      { Constructor }
	 *
	 * @param[in]  <unnamed>  { A graph representing the network. }
	 */
	InformationNetwork(amon::Graph g);

	/**
	 * Returns a series of pairs (r, d), where r is the rate out degree of the i-th node 
	 * and d is the depth of reach of this user in the observed network.
	 *
	 * @brief      { Returns a series of pairs (r, d). }
	 *
	 * @return     { A vector containing the (r, d) pairs. }
	 */
	std::vector< std::pair<int, int> > informationDepth();

private:
	amon::Graph g;
	const unsigned int NUM_THREADS = std::thread::hardware_concurrency();
};
}

#endif 