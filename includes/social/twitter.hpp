#ifndef __TWITTER_H__
#define __TWITTER_H__

#include <graph/graph.hpp>
#include <util/json/json.hpp>
#include <string>
#include <queue>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <thread>

namespace amon {

/*
 * This class loads a series of tweets in JSON from a file to analyze.
 */
class TweetLoader {
public:

	TweetLoader();
	TweetLoader(const TweetLoader& other);

	/**
	 * @brief      { Constructor }
	 *
	 * @param[in]  jsonFile  { Path to the file containing json tweets by line. }
	 * @param[in]  p { The percentage of the input file to load. }
	 */
	void genRetweetNetwork(std::string jsonFile, double p);


	/**
	 * @brief      { Generates a network based on mentions. Saves hashtags with timestamps per node 
	 * 					for later cascade-generations. }
	 *
	 * @param[in]  jsonFile  { Path to the file containing json tweets by line. }
	 * @param[in]  p { The percentage of the input file to load. }
	 */
	void loadCompleteNetwork(std::string jsonFile, double p);

	/**
	 * @brief      { Returns the number of hashtags in the dataset. }
	 *
	 * @return     { The number of hashtags in the dataset. }
	 */
	int getNumberOfHashtags();

	/**
	 * @brief      { Returns the loaded network. }
	 *             
	 * @return     { An amon::Graph containing the loaded network. }
	 */
	amon::Graph getSocialNetwork();


private:	
	amon::Graph socialNetwork;
	std::queue <std::string> Q;
	std::mutex qMutex;

	// Users in the input tweets file
	std::unordered_map<std::string, int> hashtags;
 	std::unordered_map<std::string, int> tweets;
 	std::unordered_map<std::string, int> users;
 	// Associates user ->  (hashtag, earliest time) 
 	std::unordered_map<int, std::unordered_map<int, int> > timestamps;

 	void loadRetweetNetwork (std::string json);

 	const unsigned short MAX_CHARS = 200;
 	const unsigned int NUM_THREADS = std::thread::hardware_concurrency();
};
}

#endif