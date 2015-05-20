
#include <fstream>
#include "highscore.h"


namespace game
{

void Highscore::init(std::string filename)
{
    leaderboards_filename = filename;
    leaderboard.clear();
    std::ifstream in (filename.c_str());
    std::pair<std::string , int> pair_buffer;
    while(in >> pair_buffer.first)
    {
        in >> pair_buffer.second;
        leaderboard.push_back(pair_buffer);
    }

}

void Highscore::add(std::string name, int score)
{
    std::pair <std::string , int> pair_buffer;
    pair_buffer.first = name;
    pair_buffer.second = score;
    leaderboard.push_back(pair_buffer);
}

void Highscore::save()
{
    std::ofstream out (leaderboards_filename.c_str());
    for(unsigned int a = 0; a < leaderboard.size() ; a++)
    {
        out<<leaderboard[a].first<<" "<<leaderboard[a].second<<std::endl;
    }
}

}
