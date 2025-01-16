#include "../hpp/Widget.hpp"

Widget::Widget(WidgetType type)
{
    this->type = type;
}

Widget::~Widget()
{
}

WidgetType Widget::getType()
{
    return this->type;
}