#include <iostream>
#include <tuple>
#include <stack>
#include "prefix.h"
using namespace std;

// insert function. need to traverse tree down, then back up 
void PrefixTree::insert(Node* node, string name, int id, string title, float completionTime,
                        vector<string> genres, string releaseDate, vector<string> platforms,
	                      vector<string> publishers) {

  // convert name[0] char to index based on whether it is ' ', 0-9, A-Z, or a-z
  int index = getIndex(name[0]);

  // if char is invalid, stop attempt to insert
  if (index == -1) return;

  // if the name is only one letter long, we have reached the end of the word
  // inserting node with node information
  if (name.length() == 1) {
    if (node->letters[index] != nullptr) {
      // set node id and completionTime values
      node->letters[index]->id = id;
      node->letters[index]->title = title;
      node->letters[index]->completionTime = completionTime;
      node->letters[index]->genres = genres;
      node->letters[index]->releaseDate = releaseDate;
      node->letters[index]->platforms = platforms;
      node->letters[index]->publishers = publishers;
    } else {
      // insert the final Node
      node->letters[index] = new Node(id, title, completionTime, genres, 
                                                    releaseDate, platforms, publishers);
    }
  }

  // checking if the current letter has been inserted at this node yet
  // name[0]-'a' converts the first letter in the word to its ascii value and to an index value
  else if (node->letters[index] != nullptr) {
    // calling the function recursively, with the name inserted minus its first letter
    this->insert(node->letters[index], name.substr(1), id, title, completionTime,
                genres, releaseDate, platforms, publishers);
  } else {
    node->letters[index] = new Node();
    this->insert(node->letters[index], name.substr(1), id, title, completionTime,
                genres, releaseDate, platforms, publishers);
  }
  return;
}

tuple<vector<string>, vector<float>, vector<vector<string>>, vector<string>, vector<vector<string>>, 
      vector<vector<string>>> PrefixTree::getAll(Node* node) {
        tuple<vector<string>, vector<float>, vector<vector<string>>, vector<string>, vector<vector<string>>, 
              vector<vector<string>>> returnAll;
        stack<Node*> prefixStack;

        prefixStack.push(node);
        
        while (prefixStack.empty() != true) {
          Node* currentNode = prefixStack.top();
          prefixStack.pop();

          if (currentNode != nullptr) {
            // if the current node has game data, update the return tuple
            if (currentNode->id != 0) {
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


vector<vector<string>> PrefixTree::getPlatforms(Node* node) {
  vector<vector<string>> returnPlatforms;
  return returnPlatforms;
}

vector<vector<string>> PrefixTree::getGenres(Node* node) {
  vector<vector<string>> returnGenres;
  return returnGenres;
}

// retrieved the node with matching name
Node* PrefixTree::retrieve(Node* node, string name) {
  int index = getIndex(name[0]);

  if (name.length() == 0) {
    // return the Node
    return node;
  } else if (node->letters[index] != nullptr) {
    // calling the function recursively, with the name inserted minus its first letter
    return this->retrieve(node->letters[index], name.substr(1));
  }
  return nullptr;
}

bool PrefixTree::nodeEmpty(array<Node*,63> nodes) {
  for (auto it = nodes.begin(); it != nodes.end(); it++) {
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

Node::~Node() {
  for (int i = 0; i < letters.size(); i ++) {
    delete letters[i];
    letters[i] = nullptr;
  }
}