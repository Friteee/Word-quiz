
#include <functional>
#include "../utility/stopwatch.h"


namespace game
{

/**
 * This animation class is used to make some changes with object during a given time
 * It should be given a function it should do
 */

class Animation
{
public:

    Animation(std::function  <void(utility::Stopwatch)> );
    void update();

private:

    utility::Stopwatch stopwatch;
    std::function  <void(utility::Stopwatch)> object_function;

};

}//end of game namespace
