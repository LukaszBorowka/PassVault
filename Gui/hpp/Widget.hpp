#pragma once

class Widget
{
public:
    virtual void render() const = 0;
    virtual ~Widget() = default;
};