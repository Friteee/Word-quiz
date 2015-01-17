#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

namespace utility
{

class Timer
{
    public:

    Timer();
    // start the timer
    void start();
    // stop the timer
    void stop();
    // pause the timer
    void pause();
    // set ticks to current
    void reload();
    // getter of ticks
    unsigned int get_ticks();

    private:

    // integer to hold current ticks since the start/reload
    unsigned int started_ticks;
    // in case timer is paused
    unsigned int paused_ticks;
    // boolean to know if timer is paused and started
    bool paused,started;
};

}// end of utility namespace

#endif // TIMER_H_INCLUDED
