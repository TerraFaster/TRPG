#include "Renderer.h"


Renderer::Renderer(
    SDL_Renderer* renderer, 
    const Size& rendererSize, 
    const std::string& texturesDir, 
    float scale
)
{
    this->renderer = renderer;
    this->textureManager = new TextureManager(renderer, texturesDir);

    this->rendererSize = rendererSize;

    this->SetScale(scale);
    
    this->SetViewPort(Point(0, 0));
}

Renderer::~Renderer()
{
    delete this->textureManager;

    for (auto& font : this->fonts)
        delete font.second;
}


void Renderer::LoadTexture(const std::string& name, const std::string& path, Point offset)
{
    this->textureManager->LoadTexture(name, path, offset);
}

void Renderer::LoadFont(const std::string& name, const std::string& path)
{
    this->textureManager->LoadTexture(name, path);
    this->fonts[name] = new BitmapFont(this->textureManager->GetTexture(name)->GetTexture());
}


Size Renderer::GetSize() const
{
    return this->rendererSize;
}


Point Renderer::GetViewPort() const
{
    return this->viewPort;
}

void Renderer::SetViewPort(const Point& viewPort)
{
    this->viewPort = viewPort;
}

void Renderer::CenterViewPortAtPosition(const Point& position)
{
    this->SetViewPort(
        position + 
        Point(
            -this->rendererSize.width / 2, 
            -this->rendererSize.height / 2
        ) * this->scale
    );
}


float Renderer::GetScale() const
{
    return this->scale;
}

void Renderer::SetScale(float scale)
{
    this->scale = scale;
}


Texture* Renderer::GetTexture(const std::string& name)
{
    return this->textureManager->GetTexture(name);
}

BitmapFont* Renderer::GetFont(const std::string& name)
{
    return this->fonts[name];
}


Point Renderer::ScreenToWorld(const Point& screenPoint) const
{
    return (screenPoint * this->scale + this->viewPort);
}


// Render primitives
void Renderer::RenderRectAt(const Point& position, const Size& size, const Color& color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_FRect rect = {
        position.x, position.y, 
        size.width, size.height
    };

    // Check if rect is out of bounds
    if (rect.x + rect.w < 0 || rect.x > this->rendererSize.width)
        return;

    if (rect.y + rect.h < 0 || rect.y > this->rendererSize.height)
        return;

    SDL_RenderRect(renderer, &rect);
}

void Renderer::RenderRectAt(const Rect& rect, const Color& color)
{
    this->RenderRectAt(rect.GetPosition(), rect.GetSize(), color);
}


void Renderer::RenderRect(const Point& position, const Size& size, const Color& color)
{    
    this->RenderRectAt(
        Point(
            (position.x - viewPort.x) / this->scale, 
            (position.y - viewPort.y) / this->scale
        ), 
        Size(
            size.width / this->scale, 
            size.height / this->scale
        ), 
        color
    );
}

void Renderer::RenderRect(const Rect& rect, const Color& color)
{
    this->RenderRect(rect.GetPosition(), rect.GetSize(), color);
}


void Renderer::RenderFilledRectAt(const Point& position, const Size& size, const Color& color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_FRect rect = {
        position.x, position.y, 
        size.width, size.height
    };

    // Check if rect is out of bounds
    if (rect.x + rect.w < 0 || rect.x > this->rendererSize.width)
        return;

    if (rect.y + rect.h < 0 || rect.y > this->rendererSize.height)
        return;

    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::RenderFilledRectAt(const Rect& rect, const Color& color)
{
    this->RenderFilledRect(rect.GetPosition(), rect.GetSize(), color);
}


void Renderer::RenderFilledRect(const Point& position, const Size& size, const Color& color)
{
    this->RenderFilledRectAt(
        Point(
            (position.x - viewPort.x) / this->scale, 
            (position.y - viewPort.y) / this->scale
        ), 
        Size(
            size.width / this->scale, 
            size.height / this->scale
        ), 
        color
    );
}

void Renderer::RenderFilledRect(const Rect& rect, const Color& color)
{
    this->RenderFilledRect(rect.GetPosition(), rect.GetSize(), color);
}


void Renderer::RenderGradientFilledRectAt(const Point& position, const Size& size, const Color& color1, const Color& color2)
{
    // Calculate the color increment for each step
    float rStep = (color2.r - color1.r) / static_cast<float>(size.width);
    float gStep = (color2.g - color1.g) / static_cast<float>(size.width);
    float bStep = (color2.b - color1.b) / static_cast<float>(size.width);
    float aStep = (color2.a - color1.a) / static_cast<float>(size.width);

    for (int i = 0; i < size.width; ++i) {
        // Interpolated color at position i
        SDL_Color currentColor = {
            static_cast<Uint8>(color1.r + rStep * i),
            static_cast<Uint8>(color1.g + gStep * i),
            static_cast<Uint8>(color1.b + bStep * i),
            static_cast<Uint8>(color1.a + aStep * i)
        };

        // Set render color
        SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);

        // Draw a vertical line (column) of the rectangle
        SDL_RenderLine(renderer, position.x + i, position.y, position.x + i, position.y + size.height - 1);
    }
}

void Renderer::RenderGradientFilledRectAt(const Rect& rect, const Color& color1, const Color& color2)
{
    this->RenderGradientFilledRectAt(rect.GetPosition(), rect.GetSize(), color1, color2);
}


void Renderer::RenderGradientFilledRect(const Point& position, const Size& size, const Color& color1, const Color& color2)
{
    this->RenderGradientFilledRectAt(
        Point(
            (position.x - viewPort.x) / this->scale, 
            (position.y - viewPort.y) / this->scale
        ), 
        Size(
            size.width / this->scale, 
            size.height / this->scale
        ), 
        color1, 
        color2
    );
}

void Renderer::RenderGradientFilledRect(const Rect& rect, const Color& color1, const Color& color2)
{
    this->RenderGradientFilledRect(rect.GetPosition(), rect.GetSize(), color1, color2);
}


// Render texture
void Renderer::RenderTextureAt(Texture* texture, const Point& position, const Size& size)
{
    SDL_FRect rect = {
        position.x, position.y, 
        size.width, size.height
    };

    // Check if rect is out of bounds
    if (rect.x + rect.w < 0 || rect.x > this->rendererSize.width)
        return;

    if (rect.y + rect.h < 0 || rect.y > this->rendererSize.height)
        return;

    SDL_RenderTexture(renderer, texture->GetTexture(), NULL, &rect);
}

void Renderer::RenderTextureAt(const std::string& name, const Point& position, const Size& size)
{
    this->RenderTextureAt(this->GetTexture(name), position, size);
}


void Renderer::RenderTexture(Texture* texture, const Point& position, const Size& size)
{
    this->RenderTextureAt(
        texture, 
        Point(
            (position.x - texture->GetOffset().x - viewPort.x) / this->scale, 
            (position.y - texture->GetOffset().y - viewPort.y) / this->scale
        ), 
        Size(
            size.width / this->scale, 
            size.height / this->scale
        )
    );
}

void Renderer::RenderTexture(const std::string& name, const Point& position, const Size& size)
{
    this->RenderTexture(this->GetTexture(name), position, size);
}


// Render text
void Renderer::RenderText(const std::string& text, const Point& position, BitmapFont* font, const Color& color, int size)
{
    SDL_Texture* texture = font->GetTexture();
    int characterSize = font->GetCharacterSize();

    int posX = position.x;
    int posY = position.y;
    float scale = static_cast<float>(size) / characterSize;

    SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(texture, color.a);

    for (char c : text)
    {
        if (c == '\n')
        {
            posX = position.x;
            posY += static_cast<int>(characterSize * scale);
        }
        else
        {
            SDL_FRect srcRect = font->GetCharacterRect(c);

            if (srcRect.w == 0)
                continue;

            SDL_FRect destRect = {
                posX, 
                posY, 
                static_cast<int>(characterSize * scale), 
                static_cast<int>(characterSize * scale)
            };
            
            SDL_RenderTexture(renderer, texture, &srcRect, &destRect);

            posX += static_cast<int>(characterSize * scale);
        }
    }
}

void Renderer::RenderText(const std::string& text, const Point& position, const std::string& font, const Color& color, int size)
{
    this->RenderText(text, position, this->fonts[font], color, size);
}


// Main rendering functions
void Renderer::PreRender()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::PostRender()
{
    SDL_RenderPresent(renderer);
}
