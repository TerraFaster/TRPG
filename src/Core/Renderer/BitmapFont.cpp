#include "BitmapFont.h"

BitmapFont::BitmapFont(SDL_Texture* texture, int characterSize, int columns)
{
    this->texture = texture;

    this->characterSize = characterSize;
    this->columns = columns;

    GenerateCharacterMap();
}

BitmapFont::~BitmapFont()
{
    SDL_DestroyTexture(this->texture);
}


void BitmapFont::GenerateCharacterMap()
{
    for (int i = 0; i < 96; ++i) {
        char character = 32 + i;  // Start from ASCII 32 (space)
        int col = i % this->columns;
        int row = i / this->columns;
        
        SDL_FRect srcRect = {
            col * this->characterSize, 
            row * this->characterSize, 
            this->characterSize - 1,
            this->characterSize
        };
        characterMap[character] = srcRect;
    }
}


SDL_Texture* BitmapFont::GetTexture() const
{
    return this->texture;
}


int BitmapFont::GetCharacterSize() const
{
    return this->characterSize;
}

int BitmapFont::GetColumns() const
{
    return this->columns;
}


SDL_FRect BitmapFont::GetCharacterRect(char c) const
{
    if (characterMap.find(c) != characterMap.end())
        return characterMap.at(c);
        
    else
        return {0, 0, 0, 0};
}
