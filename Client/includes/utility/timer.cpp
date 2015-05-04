
#include "timer.h"
#include <cstdio>

namespace utility
{

void Timer::set_time(unsigned int init_time)
{
    time = init_time;
}

// set function
void Timer::set_function(std::function<void()> init_function)
{
    script = init_function;
}
// update the timer to see if
void Timer::update()
{
    if(started && stopwatch.get_ticks() > time)
    {
        if(script)
            script();
        else
            printf("Warning : no function specified for timer\n");
        started = false;
        stopwatch.reload();
        stopwatch.stop();
    }
}

void Timer::start()
{
    started = true;
    stopwatch.start();
}



}//end of utility namespace
