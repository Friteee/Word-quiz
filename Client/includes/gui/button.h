#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

class Button : public Gui_element
{
public:
    Button(utility::Configuration * config, std::string init_text , int x , int y);
    void show()override;
    void update()override;
    void init_function(std::function<void()> init_on_click);
    void handle_click(int x, int y);
    ~Button();
private:
    bool is_clicked = false;
};

#endif // BUTTON_H_INCLUDED
