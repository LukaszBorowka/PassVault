#pragma once

#include <iostream>
#include <functional>

#include "Window.hpp"
#include "Widget.hpp"
#include "Size.hpp"
#include "Point.hpp"

class Button
{
public:

    Button();
    ~Button();

    void setSize(Size size);
    Size getSize();

    void setPosition(Point position);
    Point getPosition();

    void setLabel(std::string label);
    std::string getLabel();

    void setOnClick(std::function<void(Button&)> on_click);

private:

    std::reference_wrapper<Window> parent_window;

    Size size;
    Point position;
    std::string label;

    std::function<void(Button&)> on_click;

    friend class Window;
};