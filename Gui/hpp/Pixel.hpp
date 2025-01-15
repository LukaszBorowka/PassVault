#pragma once

struct Pixel // pseudo pixel, character in screen buffer
{
    char ch;
    Pixel (char ch = ' ') : ch(ch) {}
};