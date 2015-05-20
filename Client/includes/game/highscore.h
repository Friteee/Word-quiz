#ifndef HIGHSCORE_H_INCLUDED
#define HIGHSCORE_H_INCLUDED

#include <utility>
#include "../utility/configuration.h"

namespace game
{

class Highscore
{
public:
    void init(std::string filename);
    std::vector<std::pair<std::string,int> > get(int quantity);
    void add (std::string, int);
    void save();
private:
    std::vector<std::pair<std::string,int> > leaderboard;
    std::string leaderboards_filename;
};

}

#endif // HIGHSCORE_H_INCLUDED
