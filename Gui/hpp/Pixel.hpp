#pragma once

struct Pixel // pseudo pixel, character in screen buffer
{
    char ch;
    std::string UniCh;
    Pixel (char ch = ' ') : ch(ch) {}
};