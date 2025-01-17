#include "../hpp/Widget.hpp"

Widget::Widget()
{
}

Widget::~Widget()
{
}

void Widget::setSize(Size size)
{
    this->size = size;
}

Size Widget::getSize()
{
    return this->size;
}

void Widget::setPosition(Point position)
{
    this->position = position;
}

Point Widget::getPosition()
{
    return this->position;
}

void Widget::setBackgroundColor(Color background_color)
{
    this->background_color = background_color;
}

Color Widget::getBackgroundColor()
{
    return this->background_color;
}

void Widget::setTextColor(Color text_color)
{
    this->text_color = text_color;
}

Color Widget::getTextColor()
{
    return this->text_color;
}

void Widget::setContent(std::string content)
{
    this->content = content;
}

std::string Widget::getContent()
{
    return this->content;
}