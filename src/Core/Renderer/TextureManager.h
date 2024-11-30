#pragma once

#include <SDL3/SDL.h>

#include <string>
#include <unordered_map>

#include "Texture.h"

class TextureManager
{
private:
    SDL_Renderer* renderer;

    std::unordered_map<std::string, Texture*> textures;

    std::string texturesDir;

    SDL_Texture* CreateMissingTexture();

public:
    TextureManager(SDL_Renderer* renderer, const std::string& texturesDir);
    ~TextureManager();

    void LoadTexture(const std::string& name, const std::string& path, const Size& size, Point offset = Point(0, 0));
    void LoadTexture(const std::string& name, const std::string& path, Point offset = Point(0, 0));

    Texture* GetTexture(const std::string& name);
};
