#pragma once

#include <SDL3/SDL.h>

#include <string>

#include <Size.h>
#include <Renderer.h>
#include <GameGUI.h>
#include <World.h>

class Game
{
private:
    static Game* instance;

    bool ready = false;

    SDL_Window* window;
    SDL_Renderer* SDLRenderer;

    Renderer* renderer;

    std::string windowTitle;
    Size windowSize;

    World* world;

    GameGUI* gui;

    void LoadAssets();
    void CreateWorld();

public:
    Game();
    ~Game();

    static Game* GetInstance();

    bool IsReady();
    
    Renderer* GetRenderer();

    void Update(float deltaTime);
    void Render(float deltaTime);
};
