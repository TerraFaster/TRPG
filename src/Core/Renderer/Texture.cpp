#include "Texture.h"

Texture::Texture(SDL_Texture* texture, Size size, const std::string& name, const std::string& path, Point offset)
{
    this->texture = texture;
    this->size = size;
    this->name = name;
    this->path = path;
    this->offset = offset;
}

Texture::~Texture()
{
    SDL_DestroyTexture(this->texture);
}


SDL_Texture* Texture::GetTexture()
{
    return this->texture;
}


Size Texture::GetSize()
{
    return this->size;
}

Point Texture::GetOffset()
{
    return this->offset;
}


std::string Texture::GetName()
{
    return this->name;
}

std::string Texture::GetPath()
{
    return this->path;
}
