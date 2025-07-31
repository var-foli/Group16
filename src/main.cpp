
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "ParseCSV.h"

using namespace std;

int main() {

    vector<Node> nodes = parseCSV("games.csv");

    int start, end;
    cout << nodes.size() << " entries!" << endl;
    cout << "Enter start index  number: ";
    cin >> start;
    cout << "Enter end index number: ";
    cin >> end;
    if (end == 0) {
        exit(0);
    }
    for (int i = start; i < end; i++) {
        printGameNode(nodes[i]);
    }

    return 0;
}