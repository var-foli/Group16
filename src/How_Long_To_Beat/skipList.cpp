
#include "skipList.h"
#include <iostream>



using namespace std;

//constructor for skip skip list nodes
skipListNode::skipListNode(int level, const Node& nodeData) {
    data = nodeData;
    forward.resize(level + 1, nullptr);
}

//initialize head node, level counter, size counter
SkipList::SkipList() {
    head = new skipListNode(0, Node{}); //dummy head, no data
    currentLevel = 0;
    size = 0;
    srand(time(nullptr)); //seed random number generator
}
//for each node added, a random level is found based on 50/50 odds
int SkipList::randLevel() {
    int level = 0;
    while ((rand() % 2) == 1) {
        level++;
    }
    return level;
}

//insert nodes to skip list, ordered by case sensitive title
void SkipList::insert(const Node& node) {
    skipListNode* current = head;

    //new random level is created for each inserted node
    int level = randLevel();

    //if new random level is greater than current level cap, update head
    if (level > currentLevel) {
        for (int i = currentLevel + 1; i <= level; i++) {
            head->forward.push_back(nullptr);
        }

        //resize nodes at level 0 to have enough forward pointers
        skipListNode* node_ptr = head->forward[0];
        while (node_ptr) {
            if (node_ptr->forward.size() < level +1) {
                node_ptr->forward.resize(level + 1, nullptr);
            }
            node_ptr = node_ptr->forward[0];
        }
        currentLevel = level;
    }

    //track the path for pointer for insertion
    vector<skipListNode*> update(currentLevel + 1);
    current = head;

    //find position to insert starting from top to bottom
    for (int i = currentLevel; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->data.title < node.title) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    //now we create a new node with it's level to insert into the list
    skipListNode* newNode = new skipListNode(level, node);
    for (int i = 0; i <= level; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
    size++;
}

//case sensitive search for title
optional<Node> SkipList::search(const string& title) {
    //cout << "Searching for " << title << endl;
    skipListNode* current = head;

    //look from top to bottom for the position
    for (int i = currentLevel; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->data.title < title) {
            //cout << current->forward[i]->data.title << endl;
            current = current->forward[i];
        }
    }

    //at level 0, we search the exact match
    current = current->forward[0];
    if (current && current->data.title == title) {
        return current->data;
    }
    else {
        return Node{};
    }
}

int SkipList::getSize() {
    return size;
}

