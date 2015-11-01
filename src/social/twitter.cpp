#include <social/twitter.hpp>
#include <util/progress_bar.hpp>
#include <string>
#include <iostream>
#include <util/pyutil.hpp>
#include <thread>

amon::TweetLoader::TweetLoader() {}

// The copy constructor
amon::TweetLoader::TweetLoader(const amon::TweetLoader& other) {
}

amon::Graph amon::TweetLoader::getSocialNetwork() {
	return socialNetwork;
}


void amon::TweetLoader::loadMentionNetwork (std::string json, int t) {
	Json::Value v;
	Json::Reader reader;

	reader.parse(json, v);

	std::string user = v["user"].asString(); 


	int p1 = v["text"].asString().find("RT @");
	bool retweet = true;
	if (p1 == std::string::npos) retweet = false; 

	qMutex.lock();
	if(!users.count(user)) {
		int i = users.size();
		users[user] = i;
		socialNetwork.addNode(i);
	} 

	for (auto h : v["hashtags"]) {
		activations[h.asString()].push_back(users[user]);
	}
	for (auto m : v["mentions"]) {
		if (!users.count(m.asString())) {
			int i = users.size();
			users[m.asString()] = i;
			
		} 
		// if (!retweet) {
		// 	socialNetwork.addDirectedEdge(users[user], users[m.asString()]);	
		// } else {
			socialNetwork.addDirectedEdge(users[m.asString()], users[user]);	
		// }
		
	}
	qMutex.unlock();
}

void amon::TweetLoader::loadRetweetNetwork (std::string json) {
	Json::Value v;
	Json::Reader reader;

	reader.parse(json, v);

	std::string rt_user;
	char usr[MAX_CHARS];

	std::string text;
	try {
		 text = v["text"].asString();
	} catch (...) {
		return;
	}

	std::string strip_text;

	int p1 = text.find("RT @");
	if (p1 == std::string::npos) return;

	sscanf(text.c_str() + p1 + 4, "%[^:]", usr);
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


void amon::TweetLoader::load (std::string jsonFile, double p, amon::TweetLoader::NetworkType type) {

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
	int T = 0;

	while (getline(in, line)) {
		tot_twt++;
		if (line.size() == 0) continue;

		Q.push(line);		
		if (Q.size() == NUM_THREADS) {
			// Spawns a thread to poll lines
			std::vector<std::thread> v;
			while (!Q.empty()) {
				if (type == amon::TweetLoader::NetworkType::Retweet) {
					v.push_back(std::thread(&amon::TweetLoader::loadRetweetNetwork, this, Q.front()));
				}  else if (type == amon::TweetLoader::NetworkType::Mention) {
					v.push_back(std::thread(&amon::TweetLoader::loadMentionNetwork, this, Q.front(), T++));
				}
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

	std::cerr << "Loaded tweets from " << socialNetwork.nodesQty() << " users\n";
}


int amon::TweetLoader::getActvationsSize(std::string tag) {
	return activations[tag].size();
}

std::vector<std::string> amon::TweetLoader::getHashtags() {
	std::vector<std::string> res;
	for (auto x : activations) {
		res.push_back(x.first);
	}
	return res;
}


boost::python::list amon::TweetLoader::getHashtags_py() {
	return toPythonList(getHashtags());
}

std::vector<int> amon::TweetLoader::getHashtagActivations(std::string tag) {
	return activations[tag];
}

boost::python::list amon::TweetLoader::getHashtagActivations_py(std::string tag) {
	return toPythonList(getHashtagActivations(tag));
}

