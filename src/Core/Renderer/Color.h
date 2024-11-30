#pragma once

#include <SDL3/SDL.h>

#include <string>

class Color
{
public:
    // Some basic colors
    static Color Black;
    static Color White;
    static Color Red;
    static Color Green;
    static Color Blue;
    static Color Yellow;
    static Color Cyan;
    static Color Magenta;
    static Color Transparent;

    Uint8 r, g, b, a;

    Color(Uint8 r = 255, Uint8 g = 255, Uint8 b = 255, Uint8 a = 255);
    Color(Uint32 hex);
    Color(const std::string& str);
};
