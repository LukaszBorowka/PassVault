#pragma once

#include <iostream>
#include <vector>
#include <functional>

#include "Gui.hpp"
#include "Size.hpp"
#include "Point.hpp"
#include "Pixel.hpp"
#include "Label.hpp"
#include "UniStr.hpp"

class Label;

class Window
{
public:

    Window();
    ~Window();

    void setTitle(std::string title);
    void setSize(Size size);

    void setOnOpen(std::function<void(Window&)> on_open);
    void setOnClose(std::function<void(Window&)> on_close);

    void addLabel(Label& Label);

private:

    std::string title;
    Size size;

    std::vector<std::vector<Pixel>> render_buffer;

    std::vector<std::reference_wrapper<Label>> Labels;

    std::function<void(Window&)> on_open;
    std::function<void(Window&)> on_close;

    void render();

    Pixel getPixelFromRender(Point point);

    friend class Gui;

};