#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <functional>
#include "stopwatch.h"

namespace utility
{

class Timer
{
public:
    // set time in milliseconds (ticks)
    void set_time(unsigned int init_time);
    // set function
    void set_function(std::function<void()> init_function);
    // update the timer to see if
    void update();
    void start();

private:
    // for handling ticks
    Stopwatch stopwatch;
    // time until next function
    int time = 0;
    // bool if started
    bool started = false;
    // function
    std::function<void()> script;
};

}//end of utility namespace

#endif // TIMER_H_INCLUDED
