#include "TextureManager.h"

#include <SDL3_image/SDL_image.h>

TextureManager::TextureManager(SDL_Renderer* renderer, const std::string& texturesDir)
{
    this->renderer = renderer;
    this->texturesDir = texturesDir;

    SDL_Texture* missingTexture = this->CreateMissingTexture();
    this->textures["missing"] = new Texture(missingTexture, Size(32, 32), "missing", "missing");
}

TextureManager::~TextureManager()
{
    for (auto& texture : textures)
    {
        SDL_DestroyTexture(texture.second->GetTexture());
        delete texture.second;
    }
}


SDL_Texture* TextureManager::CreateMissingTexture()
{
    // Programmaticaly create black-and-purple checkerboard texture for missing textures
    SDL_Surface* surface = SDL_CreateSurface(100, 100, SDL_PIXELFORMAT_RGBA8888);

    const SDL_PixelFormatDetails* format = SDL_GetPixelFormatDetails(surface->format);

    SDL_FillSurfaceRect(surface, NULL, SDL_MapRGB(format, NULL, 0, 0, 0));

    // Draw checkerboard pattern
    for (int y = 0; y < 100; y++)
    {
        for (int x = 0; x < 100; x++)
        {
            if ((x / 10 + y / 10) % 2 == 0)
            {
                SDL_FillSurfaceRect(
                    surface, new SDL_Rect{x, y, 1, 1}, 
                    SDL_MapRGB(format, NULL, 255, 0, 255)
                );
            }
        }
    }

    SDL_Texture* missingTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_DestroySurface(surface);

    return missingTexture;
}


void TextureManager::LoadTexture(const std::string& name, const std::string& path, const Size& size, Point offset)
{
    std::string filePath = texturesDir + path;

    // Load texture
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());

    if (texture == NULL)
    {
        SDL_Log("Failed to load texture: %s (%s)", filePath.c_str(), SDL_GetError());
        return;
    }

    textures[name] = new Texture(texture, size, name, path, offset);
}

void TextureManager::LoadTexture(const std::string& name, const std::string& path, Point offset)
{
    std::string filePath = texturesDir + path;

    // Load texture
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());

    if (texture == NULL)
    {
        SDL_Log("Failed to load texture: %s (%s)", filePath.c_str(), SDL_GetError());
        return;
    }

    // Get texture size
    float width, height;
    SDL_GetTextureSize(texture, &width, &height);

    textures[name] = new Texture(texture, Size(width, height), name, path, offset);
}


Texture* TextureManager::GetTexture(const std::string& name)
{
    if (textures.find(name) != textures.end())
        return textures[name];

    return textures["missing"];
}
