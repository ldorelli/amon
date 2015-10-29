#ifndef __CASCADE_HPP__
#define __CASCADE_HPP__

#include <graph/graph.hpp>
#include <vector>
#include <random>
#include <unordered_set>
#include <boost/python.hpp>
#include <util/progress_bar.hpp>
#include <string>

/**
 *	Implements a binary with threshold cascade model. 
 *	Thresholds are taken from an uniform distribution. 
 */
namespace amon {

class CascadeModel {
public:

	/**
	 * @brief      { Creates a cascade model only with a graph. }
	 *
	 * @param[in]  g     { The graph. }
	 */
	CascadeModel(amon::Graph g);

	/**
	 * @brief      { Creates a cascade model based on a previous generated graph. }
	 *
	 * @param[in]  g     { The graph. }
	 * @param[in]  f	 { Fraction of initial innovators. } 
	 * @param[in]  adoptionThreshold { The threshold of neighboors necessary to trigger a cascade effect. }
	 * @param[in] innovatorModel 
	 * 				{ default: random innovators, 'degree': the highest degree nodes
	 * 						'bet': highest betweeness nodes }
	 */
	CascadeModel(amon::Graph g, double f, double adoptionThreshold, std::string innovatorModel);

	/**
	 * @brief      { Calculates an iteration randomly.  }
	 *
	 * @return     { True if the cascade is finished. }
	 */
	bool step ();

	/**
	 * This method runds a cascading proccess with known data.
	 * The THRESHOLD parameter is then estimated from the data for every vertex.
	 * The vectors innovators and earlyAdopters are generated.
	 * The cascading graph is also generated.
	 *  
	 * @brief      { Simulates the spreading procccess knowing the affected nodes and orders. }
	 *
	 * @param[in]  record  { A vector containing ordered observations of the spreading proccess. }
	 */
	void runFromRecord(std::vector<int> record);

	/**
	 * @brief      { Returns the maximal distance from an active node to the inovators. }
	 *
	 * @return     { The maximal distance from an active node to innovators. }
	 */
	int reachFromInnovators();

	amon::Graph getCascades();
	

	std::unordered_set<int> getInnovators();
	
	std::unordered_set<int> getEarlyAdopters();
	
	std::unordered_map<int, double> getEstimatedThreshold();

	boost::python::dict getEstimatedThreshold_py();
	boost::python::list getInnovators_py();
	boost::python::list getEarlyAdopters_py();	
	void runFromRecord_py(boost::python::list);

private:
	std::vector<int> depth;
	amon::ProgressBar bar;
	std::vector <double> thresholds;
	std::vector <bool> states;
	// The actual cascade generated
	std::priority_queue< std::pair<double, int> > susceptibleNodes;
	std::unordered_set<int> earlyAdopters, innovators;
	std::unordered_map<int, double> estimatedThreshold;
	amon::Graph cascades;
	amon::Graph g;
};

class CascadeAnalyzer {

};
}

#endif 