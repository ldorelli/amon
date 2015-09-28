#include <csys/epidemics.hpp>
#include <graph/graph.hpp>
#include <iostream>

amon::SISModel::SISModel (amon::Graph g, double ip, double cp, int firstInfected) {
	this->g = g;
	infectionP = ip;
	cureP = cp;
	gen = std::mt19937(rd());
	currState = 0;
	for (int i = 0; i < 2; ++i) 
		states[i] = std::vector<int> (g.nodesQty(), 0);
	states[currState][firstInfected] = 1;
}


amon::SISModel::SISModel (amon::Graph g, double ip, double cp, int firstInfected, int seed) {
	this->g = g;
	infectionP = ip;
	cureP = cp;
	gen = std::mt19937(seed);
	currState = 0;
	for (int i = 0; i < 2; ++i) 
		states[i] = std::vector<int> (g.nodesQty(), 0);
	states[currState][firstInfected] = 1;
}

// 1 - INFECTED
// 0 - SUSCEPTIBLE
void amon::SISModel::step() {
	std::uniform_real_distribution<double> sample(0, 1);
	int nextState = !currState;
	
	for (int i = 0; i < g.nodesQty(); ++i) {
		states[nextState][i] = states[currState][i];
	}

	for (int i = 0; i < g.nodesQty(); ++i) {
		if (states[currState][i] == 1) {
			for (auto e = g.neighboorsBegin(i); e != g.neighboorsEnd(i); g.nextNeighboor(e, i)) {
				int v = e->first;
				if (states[currState][v]) continue;
				double p = sample(gen);
				if (p <= infectionP) {
					states[nextState][v] = 1;
				}
			}
		}
	}

	for (int i = 0; i < g.nodesQty(); ++i) {
		if (states[nextState][i] == 1) {
			double p = sample(gen);
			if (p <= cureP) {
				states[nextState][i] = 0;
			}
		}
	}
	
	currState = !currState;
}

double amon::SISModel::infectedRatio() {
	double res = 0.0;
	for (int i = 0; i < g.nodesQty(); ++i) {	
		if (states[currState][i] == 1) res += 1.0;	
	}
	return res/(double)g.nodesQty();
}