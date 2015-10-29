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
#include <boost/python.hpp>

namespace amon {

/*
 * This class loads a series of tweets in JSON from a file to analyze.
 */
class TweetLoader {
public:

	enum NetworkType {
		Retweet, Mention, Hashtag 
	};

	TweetLoader();
	TweetLoader(const TweetLoader& other);

	/**
	 * @brief      { Loads tweets from a json. }
	 *
	 * @param[in]  jsonFile  { Path to the file containing json tweets by line. }
	 * @param[in]  p { The percentage of the input file to load. }
	 * @param[in]  type { The type of network to construct. }
	 */
	void load (std::string jsonFile, double p, NetworkType type);


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

	/**
	 * @brief      { Returns a list of hashtags in the dataset. }
	 *
	 * @return     { A std::vector with the hashtags }
	 */
	std::vector<std::string> getHashtags();

	/**
	 * @brief      { Get a chronological order of users who shared the hashtag. }
	 *
	 * @param[in]  tag   { The shared hashtag }
	 *
	 * @return     { A std::vector with the users.  }
	 */
	std::vector<int> getHashtagActivations(std::string tag);

	/**
	 * @brief      { Returns the number of ocurrences of a hashtag. }
	 *
	 * @return     { description_of_the_return_value }
	 */
	int getActvationsSize(std::string hashtag);

	boost::python::list getHashtags_py();
	boost::python::list getHashtagActivations_py(std::string tag);

private:	
	amon::Graph socialNetwork;
	std::queue <std::string> Q;
	std::mutex qMutex;

	// Users in the input tweets file
 	std::unordered_map<std::string, int> tweets;
 	std::unordered_map<std::string, int> users;

 	// Associates hashtag -> users that activated it chronologically
 	std::unordered_map<std::string, std::vector<int> > activations;


 	void loadRetweetNetwork (std::string json);
 	void loadMentionNetwork (std::string json, int t);

 	const unsigned short MAX_CHARS = 200;
 	const unsigned int NUM_THREADS = std::thread::hardware_concurrency();
};
}

#endif