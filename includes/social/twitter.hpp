#ifndef __TWITTER_H__
#define __TWITTER_H__

#include <graph.hpp>
#include <json.hpp>
#include <string>
#include <queue>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <future>

namespace amon {

/*
 * This class loads a series of tweets in JSON from a file to analyze.
 */
class TweetLoader {
public:

	enum NetworkType {
		FOLLOWING_NETWORK, HASHTAG_NETWORK
	};


	/**
	 * @brief      { Constructor }
	 *
	 * @param[in]  jsonFile  { Path to the file containing json tweets by line. }
	 * @param[in]  p { The percentage of the input file to load. }
	 */
	TweetLoader(std::string jsonFile, double p, NetworkType type);

	/**
	 * @brief      { Returns the loaded network. }
	 *             
	 * @return     { An amon::Graph containing the loaded network. }
	 */
	amon::Graph getSocialNetwork();


private:	
	amon::Graph socialNetwork;
	std::queue <std::string> Q;

	// Following Network Parameters
 	std::unordered_map<std::string, int> users;

 	void loadFollowers (std::string json);

 	const unsigned int NUM_THREADS = 4;
};
}

#endif