#ifndef PARSECSV_H
#define PARSECSV_H
#include <string>
#include <vector>
using namespace std;

//Node contains relevant fields for our use
struct Node {
    string title;
    float completion;
    vector<string> publisher;
    vector<string> genres;
    vector<string> platforms;
    string release = "N/A"; //Default if empty
};

//We take the filename and return a vector of nodes to use with our search functions
vector<Node> parseCSV(const string& filename);
//In case we need to peek into the content of specific entries, this prints them out
void printGameNode(const Node& node);


#endif //PARSECSV_H
