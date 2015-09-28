#ifndef __INTERPRETER_HPP__
#define __INTERPRETER_HPP__

#include <fstream>
#include <iostream>
#include <graph/graph.hpp>
#include <social/twitter.hpp>
#include <util/progress_bar.hpp>
#include <map>

/**
 *  This class should be a very simple interpreter to work with amon.
 *  The allowed commands are: 
 *  g = network() -> creates a network 
 *  add_node g // adds a node to g (if g is a network)
 *  add_edge a - b [w] g // adds an undirected edge from a - b, weight is optional
 *  add_edge a - b [w] g // adds a directed edge from a - b, weight is optional
 *  read_edges filename g // reads edges from input file to g 
 *  tweeter_follower filename g // builds a twitter follower network into g
 *  global_clustering g // prints 	 the global clustering coeff. of g
 *  where A is a return variable from B. 
 */
 namespace amon {
 class Interpreter
 {
 public:
 	Interpreter(){}
 	
 	void runInteractive();
 	/**
 	 * @brief      { Runs the script in the file. }
 	 *
 	 * @param[in]  filename  { The script file name. }
 	 */
 	void runScript(std::string filename);

 	/**
 	 * @brief      { Interprets a single line. }
 	 *
 	 * @param      line  { The line to interpret. }
 	 * @param[in]  ln    { The line number }
 	 * @param[in]  st    { The current position in line. }
 	 */
 	void interpret (std::string& line, int ln, int st);


private:
 	// current command
 	std::string ccmd;
 	
 	std::map<std::string, amon::Graph> graphs;
 };
}

#endif