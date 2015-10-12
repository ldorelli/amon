#include <social/twitter.hpp>
#include <util/progress_bar.hpp>
#include <string>
#include <iostream>
#include <thread>

amon::TweetLoader::TweetLoader() {}

// The copy constructor
amon::TweetLoader::TweetLoader(const amon::TweetLoader& other) {
}

amon::Graph amon::TweetLoader::getSocialNetwork() {
	return socialNetwork;
}

void amon::TweetLoader::loadRetweetNetwork (std::string json) {
	Json::Value v;
	Json::Reader reader;
	reader.parse(json, v);

	std::string rt_user;

	char usr[MAX_CHARS];

	std::string text = v["text"].asString();
	std::string strip_text;

	int p1 = text.find("RT @:");
	sscanf(text.c_str() + p1 + 5, "%[^:]", usr);
	rt_user = usr;
	// Get the tweet
	for (int i = p1 + 5 + rt_user.size() + 2; i < (int) text.size(); ++i) {
		strip_text += text[i]; 
	}

	std::string user = v["user"].asString(); 

	qMutex.lock();
	
	if (tweets.count(strip_text) == 0) tweets[strip_text] = tweets.size();

	if(!users.count(user)) {
		int i = users.size();
		users[user] = i;
		socialNetwork.addNode(i);
	} 

	if (!users.count(rt_user)) {
		int i = users.size();
		users[rt_user] = i;
		socialNetwork.addNode(i);
	} 
	
	socialNetwork.addDirectedEdge(users[rt_user], users[user], tweets[strip_text]);
	qMutex.unlock(); 
}


void amon::TweetLoader::genRetweetNetwork(std::string jsonFile, double p) {

	std::string line;

	std::fstream in(jsonFile, std::ios::in);
	
	in.seekg(0, in.end);
	long long totc = in.tellg();
	in.close();

	in.open(jsonFile, std::ios::in);
	Json::Reader reader;
	amon::ProgressBar bar(totc, 0.0001);

	std::cerr << "Loading tweets network...[" << NUM_THREADS << " threads]\n";
	
	std::ios::sync_with_stdio(false);
	int tot_twt = 0;

	while (getline(in, line)) {
		tot_twt++;
		if (line.size() == 0) continue;

		Q.push(line);		
		if (Q.size() == NUM_THREADS) {
			// Spawns a thread to poll lines
			std::vector<std::thread> v;
			while (!Q.empty()) {
				v.push_back(std::thread(&amon::TweetLoader::loadRetweetNetwork, this, Q.front()));
				Q.pop();
			}
			for (auto& t : v) {
				t.join();
			}
		}
		bar += line.size();
		if (bar.progress() >= p) break;
	}

	while (!Q.empty()) {
		loadRetweetNetwork(Q.front());
		Q.pop();
	}

	std::cerr << std::endl << tweets.size() << " unique tweets from " << tot_twt << std::endl;
	std::cerr << "Loaded tweets from " << socialNetwork.nodesQty() << " users\n";
}