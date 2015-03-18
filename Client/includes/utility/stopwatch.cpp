#include "stopwatch.h"
#include <SDL.h>

namespace utility
{

/**
 *  Stopwatch constructor
 */
Stopwatch::Stopwatch()
{
    started_ticks=SDL_GetTicks();
    paused_ticks=0;
    paused=false;
    started=false;
}

/**
 * Function to get ticks from the last time stopwatch was used
 * Ticks are returned as milliseconds, so be cautious when using stopwatch for seconds
 */
unsigned int Stopwatch::get_ticks()
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
 * Function to start the stopwatch
 */
void Stopwatch::start()
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
 * Function to stop the stopwatch
 */
void Stopwatch::stop()
{
    started=false;
}

/**
 * Function to pause the stopwatch
 * The stopwatch doesn't count ticks when paused
 */
void Stopwatch::pause()
{
    paused=true;
}

/**
 * Function to reload the stopwatch to 0 milliseconds
 */
void Stopwatch::reload()
{
    started_ticks=SDL_GetTicks();
}

}// end of utility namespace

