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

void Window::addWidget(Widget& widget)
{
    this->widgets.push_back(widget);
}

void Window::render()
{
    // example
    for (auto& row : this->render_buffer)
    {
        for (Pixel& pixel : row)
        {
            pixel.ch = ' ';
            pixel.UniCh = " ";
        }
    }

    for (auto& widget : this->widgets)
    {
        //UniStr str(widget.get().content);
        UniStr str = widget.get().content;

        for (int i = 0; i < str.length(); i++)
        {
            if (widget.get().content[i] == '\0') break;
            const Point pos(widget.get().position.x + i, widget.get().position.y);
            if (pos.x < this->size.w && pos.y < this->size.h && i < widget.get().content.size()) this->render_buffer[pos.x][pos.y].UniCh = str.getUniChar(i);
        }
    }
}

Pixel Window::getPixelFromRender(Point point)
{
    return render_buffer[point.x][point.y];
}