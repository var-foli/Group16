
#include "ParseCSV.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>


using namespace std;


//Platforms,Publishers, Genres are often stored in double quotes. These fields will be stored into vectors of strings
vector<string> dblQuotes(const string& dblQuotedField) {
    vector<string> tokens;
    string token;
    bool first = true;

    for (char ch : dblQuotedField) {
        if (ch == ',') {
            if (!first) {
                while (!token.empty() && token[0] == ' ') {
                    token.erase(0,1);
                }
            }
            tokens.push_back(token);
            token.clear();
            first = false;
        } else {
            token += ch;
        }
    }
    if (!first) {
        while (!token.empty() && token[0] == ' ') {
            token.erase(0,1);
        }
    }
    tokens.push_back(token);

    return tokens;
}

//Removing non-alphanumeric characters from the title string
string scrub(const string& title) {
    string result;
    for (char c : title) {
        if (isalnum(c) || c == ' ') {
            result += c;
        }
    }
    //removing extra spaces that might occur when characters are removed
    string corrected_spaces;
    bool space_present = false;

    for (char c : result) {
        if (c == ' ') {
            if (!space_present) {
                corrected_spaces += c;
                space_present = true;
            }
        } else {
            corrected_spaces += c;
            space_present = false;
        }
    }


    return corrected_spaces;
}

//clamping float value to 2 decimal points
float clamp(float value) {
    float scale = pow(10.0f, 2);
    return round(value * scale) / scale;
}

//taking the file name, we will read through the csv file and store the entries into a vector of nodes
vector<Node> parseCSV(const string& filename) {
    ifstream file(filename);
    string line;
    vector<Node> result;

    //A vector of columns takes all the csv fields. We store only relevant fields into our nodes
    while (getline(file, line)) {
        Node node;
        vector<string> cols;
        string token;
        bool dblQuoted = false;
        string field;

        //Looking for fields with double quotes to distinguish those commas from the rest of the columns
        for (size_t i = 0; i < line.size(); i++) {
            char c = line[i];
            if (c == '"') {
                dblQuoted = !dblQuoted;
            } else if (c == ',' && !dblQuoted) {
                cols.push_back(field);
                field.clear();
            } else {
                field += c;
            }
        }
        cols.push_back(field);
        //before any nodes are pushed back, an exception handles completion times that will be thrown out if empty
        try {
            node.title = scrub(cols[1]);
            node.completion = clamp(stof(cols[2]));
        } catch (...) {
            continue;
        }
        //Double quote areas will be stored as vectors of strings
        node.publisher = dblQuotes(cols[10].empty() ? "N/A" : cols[10]);
        node.platforms = dblQuotes(cols[11].empty() ? "N/A" : cols[11]);
        node.genres = dblQuotes(cols[12].empty() ? "N/A" : cols[12]);
        // node.release = cols[13];
        node.release = cols[13].empty() ? "N/A" : cols[13];

        result.push_back(node);
    }
    return result;
}

//A function that can print out node entries
void printGameNode(const Node& node) {
    cout << "Title: " << node.title << endl;
    cout << "Completion Time: " << node.completion << endl;
    cout << "Publisher: ";
    for (auto& b : node.publisher) {
        cout << b << " ";
    }
    cout << endl;
    cout << "Platforms: ";
    for (auto& p : node.platforms) {
        cout << p << " ";
    }
    cout << endl;
    cout<< "Genres: ";
    for (auto& g : node.genres) {
        cout << g << " ";
    }
    cout << endl;
    cout << "Release: " << node.release << endl;
    cout << endl;
}
