#include "../hpp/Label.hpp"

Label::Label()
{
}

Label::~Label()
{
}

void Label::setSize(Size size)
{
    this->size = size;
}

Size Label::getSize()
{
    return this->size;
}

void Label::setPosition(Point position)
{
    this->position = position;
}

Point Label::getPosition()
{
    return this->position;
}

void Label::setBackgroundColor(Color background_color)
{
    this->background_color = background_color;
}

Color Label::getBackgroundColor()
{
    return this->background_color;
}

void Label::setTextColor(Color text_color)
{
    this->text_color = text_color;
}

Color Label::getTextColor()
{
    return this->text_color;
}

void Label::setContent(std::string content)
{
    this->content = content;
}

std::string Label::getContent()
{
    return this->content;
}