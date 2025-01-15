#pragma once

#include <iostream>
#include <functional>

#include "Window.hpp"
#include "Widget.hpp"
#include "Size.hpp"
#include "Point.hpp"

class Textbox : public Widget
{
public:

    Textbox();
    ~Textbox();

    void setSize(Size size);
    Size getSize();

    void setPosition(Point position);
    Point getPosition();

    void setContent(std::string content);
    std::string getLabel();

private:

    std::reference_wrapper<Window> parent_window;

    Size size;
    Point position;
    std::string content;

};