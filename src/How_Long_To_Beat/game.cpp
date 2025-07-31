#include "game.h"
#include <iostream>

Game::Game() {}

Game::Game(string _name, string _avgDuration, vector<string> _genres, string _releaseDate, vector<string> _platforms, vector<string> _publishers){
    this->name = _name;
    this->avgDuration = _avgDuration;
    this->genres = vectorToStr(_genres);
    this->releaseDate = _releaseDate;
    this->platforms = vectorToStr(_platforms);
    this->publishers = vectorToStr(_publishers);
}

string Game::vectorToStr(vector<string> input)
{
    string s = "";
    for(const string& str : input){
        // std::cout << str << std::endl;
        s += str + "\n";
    }
    return s;
}

