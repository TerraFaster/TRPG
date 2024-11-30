#include "Color.h"

// Some basic colors
Color Color::Black = Color(0, 0, 0);
Color Color::White = Color(255, 255, 255);
Color Color::Red = Color(255, 0, 0);
Color Color::Green = Color(0, 255, 0);
Color Color::Blue = Color(0, 0, 255);
Color Color::Yellow = Color(255, 255, 0);
Color Color::Cyan = Color(0, 255, 255);
Color Color::Magenta = Color(255, 0, 255);
Color Color::Transparent = Color(0, 0, 0, 0);

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color::Color(Uint32 hex)
{
    this->r = (hex >> 24) & 0xFF;
    this->g = (hex >> 16) & 0xFF;
    this->b = (hex >> 8) & 0xFF;
    this->a = hex & 0xFF;
}

Color::Color(const std::string& str)
{
    if (str[0] == '#')
    {
        if (str.length() == 6)
        {
            this->r = std::stoi(str.substr(0, 2), nullptr, 16);
            this->g = std::stoi(str.substr(2, 2), nullptr, 16);
            this->b = std::stoi(str.substr(4, 2), nullptr, 16);
            this->a = 255;
        }
        else if (str.length() == 8)
        {
            this->r = std::stoi(str.substr(0, 2), nullptr, 16);
            this->g = std::stoi(str.substr(2, 2), nullptr, 16);
            this->b = std::stoi(str.substr(4, 2), nullptr, 16);
            this->a = std::stoi(str.substr(6, 2), nullptr, 16);
        }
    }
    else
    {
        this->r = 255;
        this->g = 255;
        this->b = 255;
        this->a = 255;

        SDL_Log("Color format not supported");
    }
}
