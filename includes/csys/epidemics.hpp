#ifndef __EPIDEMICS_HPP__
#define __EPIDEMICS_HPP__

#include <graph/graph.hpp>
#include <vector>
#include <random> 

namespace amon {

class SISModel {

public:
	/**
	 * Constructor
	 * @param g The network
	 * @param infectionP The infection probability
	 * @param cureP The cure probability
	 * @param firstInfected The first infected node
	 */
	SISModel (amon::Graph g, double infectionP, 
		double cureP, int firstInfected);


	/**
	 * @brief      Constructor
	 *
	 * @param[in]  g           { The network }
	 * @param[in]  infectionP  { Infection probability  }
	 * @param[in]  cureP       { Cure probability }
	 * @param[in]  firstInfected {The first infected seed}
	 * @param[in]  seed        { Seed for the random numbers }
	 */
	SISModel (amon::Graph g, double infectionP, double cureP, 
		int firstInfected, int seed);

	/**
	 * Steps on next moment of the simulation.
	 */
	void step();

	/**
	 * Returns the current infected ratio Infected/n_individuals
	 * @return The ratio of infected individuals.
	 */ 
	double infectedRatio();

private:
	amon::Graph g; 
	int currState;
	std::vector<int> states[2];
	double infectionP, cureP;
	std::random_device rd;
	std::mt19937 gen;
};
};

#endif