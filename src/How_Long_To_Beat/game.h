#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
using std::string;
using std::vector;

class Game
{
public:
    Game();
    Game(string _name, string _avgDuration, vector<string> _genres, string _releaseDate, vector<string> _platforms, vector<string> _publishers);
    string name;
    string avgDuration;
    string genres;
    string releaseDate;
    string platforms;
    string publishers;
    static string vectorToStr(vector<string> input);
};

#endif // GAME_H
