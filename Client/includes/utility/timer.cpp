#include "timer.h"
#include <SDL.h>

namespace utility
{

/**
 *  Timer constructor
 */
Timer::Timer()
{
    started_ticks=SDL_GetTicks();
    paused_ticks=0;
    paused=false;
    started=false;
}

/**
 * Function to get ticks from the last time timer was used
 * Ticks are returned as milliseconds, so be cautious when using timer for seconds
 */
unsigned int Timer::get_ticks()
{
    if(!started)
    {
        return 0;
    }
    else if(paused)
    {
        return paused_ticks-started_ticks;
    }
    else
    {
        return SDL_GetTicks()-started_ticks;
    }
}

/**
 * Function to start the timer
 */
void Timer::start()
{
    if(paused==false)
    {
        started_ticks=SDL_GetTicks();
        started=true;
    }
    else
    {
        paused=false;
        started_ticks=SDL_GetTicks()-paused_ticks+started_ticks;
    }
}

/**
 * Function to stop the timer
 */
void Timer::stop()
{
    started=false;
}

/**
 * Function to pause the timer
 * The timer doesn't count ticks when paused
 */
void Timer::pause()
{
    paused=true;
}

/**
 * Function to reload the timer to 0 milliseconds
 */
void Timer::reload()
{
    started_ticks=SDL_GetTicks();
}

}// end of utility namespace

