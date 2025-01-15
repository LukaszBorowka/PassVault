#include "../hpp/Button.hpp"

Button::Button()
{
    
}

Button::~Button()
{

}

void Button::setSize(Size size)
{
    this->size = size;
}

Size Button::getSize()
{
    return this->size;
}

void Button::setPosition(Point position)
{
    this->position = position;
}

Point Button::getPosition()
{
    return this->position;
}

void Button::setLabel(std::string label)
{
    this->label = label;
}

std::string Button::getLabel()
{
    return this->label;
}