#include "../hpp/Window.hpp"

Window::Window()
{
    //std::cout << "creating window...\n";
}

Window::~Window()
{
    //std::cout << "destrying window...\n";
}

void Window::setTitle(std::string title)
{
    this->title = title;
}

void Window::setSize(Size size)
{
    this->size = size;
    
    this->render_buffer.resize(size.w);
    for (auto& col : this->render_buffer) col.resize(size.h);
}

void Window::setOnOpen(std::function<void(Window&)> on_open)
{
    this->on_open = on_open;
}

void Window::setOnClose(std::function<void(Window&)> on_close)
{
    this->on_close = on_close;
}

void Window::render()
{
    // example
    for (auto& row : this->render_buffer)
    {
        for (Pixel& pixel : row) pixel.ch = ' ';
    }
}

Pixel Window::getPixelFromRender(Point point)
{
    return render_buffer[point.x][point.y];
}