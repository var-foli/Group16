
#ifndef SKIPLIST_H
#define SKIPLIST_H


#include <vector>
#include <string>
#include "ParseCSV.h"
#include <optional>

using namespace std;

struct skipListNode {
    Node data;
    vector<skipListNode*> forward;
    skipListNode(int level, const Node& nodeData);
};

class SkipList {
private:
    skipListNode* head;
    int currentLevel;
    int size;
    int randLevel();

public:

    SkipList();
    void insert(const Node& node);
    optional<Node> search(const string& title);
    int getSize();

};

#endif //SKIPLIST_H
