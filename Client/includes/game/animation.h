
#include <functional>
#include "../utility/timer.h"


namespace game
{

/**
 * This animation class is used to make some changes with object during a given time
 * It should be given a function it should do
 */

class Animation
{
public:

    Animation(std::function  <void(utility::Timer)> );
    void update();

private:

    utility::Timer timer;
    std::function  <void(utility::Timer)> object_function;

};

}//end of game namespace
