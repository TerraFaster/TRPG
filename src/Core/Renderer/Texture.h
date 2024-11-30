#pragma once

#include <SDL3/SDL.h>

#include <string>

#include <Point.h>
#include <Size.h>


class Texture
{
private:
    SDL_Texture* texture;
    
    Size size;
    Point offset;

    std::string name;
    std::string path;

public:
    Texture(SDL_Texture* texture, Size size, const std::string& name, const std::string& path, Point offset = Point(0, 0));
    ~Texture();

    SDL_Texture* GetTexture();

    Size GetSize();
    Point GetOffset();

    std::string GetName();
    std::string GetPath();
};
