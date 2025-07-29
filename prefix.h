#pragma once
#include <string>
#include <vector>
#include <array>
using namespace std;


struct PrefixNode {
	int id;
	string title;
  float completionTime;
	vector<string> genres;
	string releaseDate;
	vector<string> platforms;
	vector<string> publishers;

	// all nodes contain a 63-length array filled with nullptrs
	array<PrefixNode*,63> letters {nullptr};

	// Default node constructor. Some nodes will just contain an array linking to other letters
	PrefixNode() {
    this->id = 0;
    this->completionTime = 0;
	}

	// PrefixNode constructor
	PrefixNode(int id, string title, float completionTime, vector<string> genres, string releaseDate, 
			vector<string> platforms, vector<string> publishers) {
    this->id = id;
		this->title = title;
    this->completionTime = completionTime;
		this->genres = genres;
		this->releaseDate = releaseDate;
		this->platforms = platforms;
		this->publishers = publishers;
	}

	~PrefixNode();
};

class PrefixTree {
	PrefixNode* head;

	public:
		void insert(PrefixNode* prefixNode, string name, int id, string title, float completionTime,
								vector<string> genres, string releaseDate, vector<string> platforms,
								vector<string> publishers);
		PrefixNode* retrieve(PrefixNode* prefixNode, string name);
		tuple<vector<string>, vector<float>, vector<vector<string>>, vector<string>, 
					vector<vector<string>>, vector<vector<string>>>getAll(PrefixNode* prefixNode);
		vector<vector<string>> PrefixTree::getPlatforms(PrefixNode* prefixNode);
		vector<vector<string>> PrefixTree::getGenres(PrefixNode* prefixNode);
		bool nodeEmpty(array<PrefixNode*,63> prefixNode);
		int getIndex(char letter);
};