#include <iostream>
#include <tuple>
#include <stack>
#include "prefix.h"
using namespace std;

// insert function. need to traverse tree down, then back up 
void PrefixTree::insert(PrefixNode* prefixNode, string name, string title, float completionTime,
                        vector<string> genres, string releaseDate, vector<string> platforms,
	                      vector<string> publishers) {
  // edge case if empty name entered
  if (name.length() == 0) {
    return;
  }
  
  // convert name[0] char to index based on whether it is ' ', 0-9, A-Z, or a-z
  int index = getIndex(name[0]);

  // if char is invalid, stop attempt to insert
  if (index == -1) return;

  // if the name is only one letter long, we have reached the end of the word
  // inserting node with node information
  if (name.length() == 1) {
    if (prefixNode->letters[index] != nullptr) {
      // set node values
      prefixNode->letters[index]->title = title;
      prefixNode->letters[index]->completionTime = completionTime;
      prefixNode->letters[index]->genres = genres;
      prefixNode->letters[index]->releaseDate = releaseDate;
      prefixNode->letters[index]->platforms = platforms;
      prefixNode->letters[index]->publishers = publishers;
    } else {
      // insert the final Node
      prefixNode->letters[index] = new PrefixNode(title, completionTime, genres, 
                                                    releaseDate, platforms, publishers);
    }
  }

  // checking if the current letter has been inserted at this node yet
  // name[0]-'a' converts the first letter in the word to its ascii value and to an index value
  else if (prefixNode->letters[index] != nullptr) {
    // calling the function recursively, with the name inserted minus its first letter
    this->insert(prefixNode->letters[index], name.substr(1), title, completionTime,
                genres, releaseDate, platforms, publishers);
  } else {
    prefixNode->letters[index] = new PrefixNode();
    this->insert(prefixNode->letters[index], name.substr(1), title, completionTime,
                genres, releaseDate, platforms, publishers);
  }
  return;
}

tuple<vector<string>, vector<float>, vector<vector<string>>, vector<string>, vector<vector<string>>, 
      vector<vector<string>>> PrefixTree::getAll(PrefixNode* prefixNode) {
        tuple<vector<string>, vector<float>, vector<vector<string>>, vector<string>, vector<vector<string>>, 
              vector<vector<string>>> returnAll;
        stack<PrefixNode*> prefixStack;

        prefixStack.push(prefixNode);
        
        while (prefixStack.empty() != true) {
          PrefixNode* currentNode = prefixStack.top();
          prefixStack.pop();

          if (currentNode != nullptr) {
            // if the current node has game data, update the return tuple
            if (currentNode->title != "~") {
              get<0>(returnAll).push_back(currentNode->title);
              get<1>(returnAll).push_back(currentNode->completionTime);
              get<2>(returnAll).push_back(currentNode->genres);
              get<3>(returnAll).push_back(currentNode->releaseDate);
              get<4>(returnAll).push_back(currentNode->platforms);
              get<5>(returnAll).push_back(currentNode->publishers);
            }
            
            // inserting the next currentNode for the stack to visit from left to right using dfs
            for (auto it = currentNode->letters.begin(); it != currentNode->letters.end(); it++) {
              if (*it != nullptr) {
                prefixStack.push(*it);
              }
            }
          }
        }
        return returnAll;
      }

tuple<vector<string>, vector<float>, vector<vector<string>>, vector<string>, vector<vector<string>>, 
      vector<vector<string>>> PrefixTree::searchName(PrefixNode* prefixNode, string name) {
  // edge case if empty name entered
  if (name.length() == 0) {
    return {};
  }
  
  // convert name[0] char to index based on whether it is ' ', 0-9, A-Z, or a-z
  int index = getIndex(name[0]);

  // if char is invalid, return an empty vector
  if (index == -1) return {};

  // if the name is only one letter long, we have reached the end of the word and return all words 
  // with that prefix
  if (name.length() == 1) {
    if (prefixNode->letters[index] != nullptr) {
      return this->getAll(prefixNode->letters[index]);
    } else {
      return {};
    }
  } else if (prefixNode->letters[index] != nullptr) {
    // calling the function recursively, with the name inserted minus its first letter
    return this->searchName(prefixNode->letters[index], name.substr(1));
  } else {
    return {};
  }
}


vector<vector<string>> PrefixTree::getPlatforms(PrefixNode* prefixNode) {
  vector<vector<string>> returnPlatforms;
  return returnPlatforms;
}

vector<vector<string>> PrefixTree::getGenres(PrefixNode* prefixNode) {
  vector<vector<string>> returnGenres;
  return returnGenres;
}

// retrieved the node with matching name
PrefixNode* PrefixTree::retrieve(PrefixNode* prefixNode, string name) {
  if (name.length() == 0) {
    // return the Node
    return prefixNode;
  } 
  
  int index = getIndex(name[0]);

  if (index == -1) {
    return nullptr;
  }
  
  if (prefixNode->letters[index] != nullptr) {
    // calling the function recursively, with the name inserted minus its first letter
    return this->retrieve(prefixNode->letters[index], name.substr(1));
  }
  return nullptr;
}

bool PrefixTree::nodeEmpty(array<PrefixNode*,63> prefixNodes) {
  for (auto it = prefixNodes.begin(); it != prefixNodes.end(); it++) {
        if (*it != nullptr) {
            return false;
        }
    }
  return true;
}

int PrefixTree::getIndex(char letter) {
  if (letter == ' ') {
    return 0;
  } else if (letter >= '0' && letter <= '9') {
    return letter - '0' + 1;
  } else if (letter >= 'A' && letter <= 'Z') {
    return letter - 'A' + 11;
  } else if (letter >= 'a' && letter <= 'z') {
    return letter - 'a' + 37;
  } else return -1;
}

PrefixNode::~PrefixNode() {
  for (int i = 0; i < letters.size(); i ++) {
    delete letters[i];
    letters[i] = nullptr;
  }
}