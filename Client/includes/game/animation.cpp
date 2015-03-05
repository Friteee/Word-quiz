
#include "animation.h"

namespace game
{

Animation::Animation(std::function  <void(utility::Timer)> init_function)
{
    object_function = init_function;
}


void Animation::update()
{
    object_function(timer);
}

}
