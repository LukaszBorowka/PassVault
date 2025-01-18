#pragma once

#include "Window.hpp"
#include "Color.hpp"
#include "Size.hpp"
#include "Point.hpp"

class Widget
{
public:

    Widget();
    ~Widget();

    void setSize(Size size);
    Size getSize();

    void setPosition(Point position);
    Point getPosition();

    void setBackgroundColor(Color background_color);
    Color getBackgroundColor();

    void setTextColor(Color text_color);
    Color getTextColor();

    void setContent(std::string content);
    std::string getContent();

private:

    Size size;
    Point position;

    Color background_color;
    Color text_color;

    std::string content;

    friend class Window;

};