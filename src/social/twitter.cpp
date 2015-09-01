#include <twitter.hpp>
#include <progress_bar.hpp>
#include <string>
#include <iostream>
#include <thread>


void amon::TweetLoader::loadFollowers(std::string json) {
	Json::Value v;
	Json::Reader reader;
	reader.parse(json, v);
}


amon::TweetLoader::TweetLoader(std::string jsonFile, double p, 
	amon::TweetLoader::NetworkType type) {

	std::string line;

	std::fstream in(jsonFile, std::ios::in);
	
	in.seekg(0, in.end);
	long long totc = in.tellg();
	in.close();

	in.open(jsonFile, std::ios::in);
	Json::Reader reader;
	amon::ProgressBar bar(totc, 0.0001);

	std::ios::sync_with_stdio(false);

	while (getline(in, line)) {
		if (line.size() == 0) continue;

		Q.push(line);		
		if (Q.size() == NUM_THREADS) {
			// Spawns a thread to poll lines
			std::vector<std::thread> v;
			while (!Q.empty()) {
				v.push_back(std::thread(&amon::TweetLoader::loadFollowers, this, line));
				Q.pop();
			}
			for (auto& t : v) {
				t.join();
			}
		}
		bar += line.size();
		if (bar.progress() >= p) break;
	}

	std::vector<std::thread> v;
	while (!Q.empty()) {
		v.push_back(std::thread(&amon::TweetLoader::loadFollowers, this, line));
		Q.pop();
	}
	for (auto& t : v) {
		t.join();
	}
}