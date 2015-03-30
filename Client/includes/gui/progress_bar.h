#ifndef PROGRESS_BAR_H_INCLUDED
#define PROGRESS_BAR_H_INCLUDED

#include <functional>
#include "../utility/stopwatch.h"
#include "gui_element.h"


namespace gui
{

class Progress_bar : public Gui_element
{

public:

    void show() override;
    void update() override;
    void handle_click(int x, int y) override;
    void set_function(std::function<void()> init_function);
    void start();
    void reset();
    ~Progress_bar();
    Progress_bar(unsigned int init_overall , SDL_Rect init_location);

private:
    //number of ticks, when some action happen
    unsigned int overall_ticks;
    // number of ticks from 0 to current position
    utility::Stopwatch current_ticks;
    // function which happens when current_ticks == overall_ticks
    std::function<void()> timer_function;
    // Rectangle for holding bar_coordinates
    SDL_Rect bar_location;
};

}//end of gui namespace

#endif // PROGRESS_BAR_H_INCLUDED
