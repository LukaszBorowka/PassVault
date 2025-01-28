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

void Window::addLabel(Label& Label)
{
    this->Labels.push_back(Label);
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

    for (auto& Label : this->Labels)
    {
        //UniStr str(Label.get().content);
        UniStr str = Label.get().content;

        for (int i = 0; i < str.length(); i++)
        {
            if (Label.get().content[i] == '\0') break;
            const Point pos(Label.get().position.x + i, Label.get().position.y);
            if (pos.x < this->size.w && pos.y < this->size.h && i < Label.get().content.size()) this->render_buffer[pos.x][pos.y].UniCh = str.getUniChar(i);
        }
    }
}

Pixel Window::getPixelFromRender(Point point)
{
    return render_buffer[point.x][point.y];
}