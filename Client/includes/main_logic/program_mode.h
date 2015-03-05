#ifndef PROGRAM_MODE_H_INCLUDED
#define PROGRAM_MODE_H_INCLUDED

#include "../utility/configuration.h"
#include <SDL.h>

namespace main_logic
{

/**
 * Base interface class for program modes
 * May include editor mode, game mode, main menu mode etc...
 */

class Program_mode
{
public:

    virtual bool run() = 0;
    virtual bool handle_input() = 0;
    virtual ~Program_mode() {}

};


} // end of main_logic namespace

#endif // PROGRAM_MODE_H_INCLUDED
