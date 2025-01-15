#pragma once

#include <iostream>
#include <vector>
#include <functional>

#include "Gui.hpp"
#include "Size.hpp"
#include "Point.hpp"
#include "Pixel.hpp"
#include "Widget.hpp"

class Window
{
public:
    Window();
    ~Window();

    void setTitle(std::string title);
    void setSize(Size size);

    void setOnOpen(std::function<void(Window&)> on_open);
    void setOnClose(std::function<void(Window&)> on_close);

private:
    std::string title;
    Size size;

    std::reference_wrapper<Gui> parent_gui;

    std::vector<std::vector<Pixel>> render_buffer;

    std::vector<std::reference_wrapper<Widget>> widgets;

    std::function<void(Window&)> on_open;
    std::function<void(Window&)> on_close;

    void render();

    Pixel getPixelFromRender(Point point);

    friend class Gui;
};