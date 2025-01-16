#pragma once

#include "Window.hpp"

enum class WidgetType
{
    Button,
    Textbox
};

class Widget
{
public:
    Widget(WidgetType type);
    ~Widget();

    WidgetType getType();

private:

    WidgetType type;
};