#pragma once

#include <SDL3/SDL.h>

#include <string>
#include <unordered_map>

#include <Point.h>
#include <Size.h>
#include <Rect.h>
#include "Color.h"
#include "TextureManager.h"
#include "BitmapFont.h"

class Renderer
{
private:
    SDL_Renderer* renderer;
    TextureManager* textureManager;

    Size rendererSize;
    Point viewPort;

    float scale = 1.0f;

    std::unordered_map<std::string, BitmapFont*> fonts;

public:
    Renderer(
        SDL_Renderer* renderer, 
        const Size& rendererSize, 
        const std::string& texturesDir, 
        float scale
    );
    ~Renderer();

    void LoadTexture(const std::string& name, const std::string& path, Point offset = Point(0, 0));
    void LoadFont(const std::string& name, const std::string& path);

    Size GetSize() const;

    Point GetViewPort() const;

    void SetViewPort(const Point& viewPort);
    void CenterViewPortAtPosition(const Point& position);

    float GetScale() const;
    void SetScale(float scale);

    Texture* GetTexture(const std::string& name);
    BitmapFont* GetFont(const std::string& name);

    Point ScreenToWorld(const Point& screenPoint) const;

    // Render primitives
    void RenderRectAt(const Point& position, const Size& size, const Color& color);
    void RenderRectAt(const Rect& rect, const Color& color);

    void RenderRect(const Point& position, const Size& size, const Color& color);
    void RenderRect(const Rect& rect, const Color& color);

    void RenderFilledRectAt(const Point& position, const Size& size, const Color& color);
    void RenderFilledRectAt(const Rect& rect, const Color& color);

    void RenderFilledRect(const Point& position, const Size& size, const Color& color);
    void RenderFilledRect(const Rect& rect, const Color& color);

    void RenderGradientFilledRectAt(const Point& position, const Size& size, const Color& color1, const Color& color2);
    void RenderGradientFilledRectAt(const Rect& rect, const Color& color1, const Color& color2);

    void RenderGradientFilledRect(const Point& position, const Size& size, const Color& color1, const Color& color2);
    void RenderGradientFilledRect(const Rect& rect, const Color& color1, const Color& color2);

    // Render texture
    void RenderTextureAt(Texture* texture, const Point& position, const Size& size);
    void RenderTextureAt(const std::string& name, const Point& position, const Size& size);

    void RenderTexture(Texture* texture, const Point& position, const Size& size);
    void RenderTexture(const std::string& name, const Point& position, const Size& size);

    // Render text
    void RenderText(const std::string& text, const Point& position, BitmapFont* font, const Color& color, int size);
    void RenderText(const std::string& text, const Point& position, const std::string& font, const Color& color, int size);
    
    // Main rendering functions
    void PreRender();
    void PostRender();
};
