#pragma once
#include <string>
#include <vector>
#include <array>
using namespace std;


struct Node {
	int id;
	string title;
  float completionTime;
	vector<string> genres;
	string releaseDate;
	vector<string> platforms;
	vector<string> publishers;

	// all nodes contain a 26-length array filled with nullptrs
	array<Node*,63> letters {nullptr};

	// Default node constructor. Some nodes will just contain an array linking to other letters
	Node() {
    this->id = 0;
    this->completionTime = 0;
	}

	// Node constructor
	Node(int id, string title, float completionTime, vector<string> genres, string releaseDate, 
			vector<string> platforms, vector<string> publishers) {
    this->id = id;
		this->title = title;
    this->completionTime = completionTime;
		this->genres = genres;
		this->releaseDate = releaseDate;
		this->platforms = platforms;
		this->publishers = publishers;
	}

	~Node();
};

class PrefixTree {
	Node* head;

	public:
		void insert(Node* node, string name, int id, string title, float completionTime,
								vector<string> genres, string releaseDate, vector<string> platforms,
								vector<string> publishers);
		Node* retrieve(Node* node, string name);
		tuple<vector<string>, vector<float>, vector<vector<string>>, vector<string>, 
					vector<vector<string>>, vector<vector<string>>>getAll(Node* node);
		vector<vector<string>> PrefixTree::getPlatforms(Node* node);
		vector<vector<string>> PrefixTree::getGenres(Node* node);
		bool nodeEmpty(array<Node*,63> nodes);
		int getIndex(char letter);
};