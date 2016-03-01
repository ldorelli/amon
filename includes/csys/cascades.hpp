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
	 * @brief      { Returns the maximal distance from an active node to the inovators. }
	 *
	 * @return     { The maximal distance from an active node to innovators. }
	 */
	int reachFromInnovators();

	/**
	 * @brief      { Returns the network representing the cascade process. }
	 *
	 * @return     { An amon::graph containing the cascade. }
	 */
	amon::Graph getCascades();

	void runFromRecordWithPaths(std::vector<int> record, int maxSteps);

	std::unordered_set<int> getInnovators();
	std::unordered_set<int> getEarlyAdopters();
	std::unordered_map<int, double> getEstimatedThreshold();

	boost::python::dict getEstimatedThreshold_py();
	boost::python::list getInnovators_py();
	boost::python::list getEarlyAdopters_py();
	void runFromRecordWIthPaths_py(boost::python::list l, int depth);

private:

	bool findCascadePath(int start, int node, int depth);

	double pathProbability;

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
