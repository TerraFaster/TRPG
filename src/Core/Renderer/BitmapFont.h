#pragma once

#include <SDL3/SDL.h>

#include <string>
#include <unordered_map>


const int DEFAULT_CHARACTER_SIZE = 16;  // Size of each character in the bitmap font
const int DEFAULT_COLUMNS = 16;         // Columns in the bitmap font texture


class BitmapFont
{
private:
    SDL_Texture* texture;

    int characterSize;
    int columns;

    std::unordered_map<char, SDL_FRect> characterMap;

    void GenerateCharacterMap();

public:
    BitmapFont(SDL_Texture* texture, int characterSize = DEFAULT_CHARACTER_SIZE, int columns = DEFAULT_COLUMNS);
    ~BitmapFont();

    SDL_Texture* GetTexture() const;

    int GetCharacterSize() const;
    int GetColumns() const;

    SDL_FRect GetCharacterRect(char c) const;
};