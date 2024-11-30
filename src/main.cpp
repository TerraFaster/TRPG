#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <GlobalFunctions.h>
#include "Game.h"


static Game *game = NULL;

float TARGET_FPS = 60.0f;
float TARGET_UPS = 60.0f;

static Uint64 updatePreviousTime = 0;
static Uint64 renderPreviousTime = 0;

static const Uint64 performanceFrequency = SDL_GetPerformanceFrequency();


int UpdateThread(void* data)
{
    while (true) {
        Uint64 currentTime = SDL_GetPerformanceCounter();
        float deltaTime = (currentTime - updatePreviousTime) / static_cast<float>(performanceFrequency);
        updatePreviousTime = currentTime;

        SetUpdateDeltaTime(deltaTime);

        if (game->IsReady())
            game->Update(deltaTime);

        if (TARGET_UPS > 0)
        {
            float targetUpdateDuration = 1.0f / TARGET_UPS;
            float elapsedUpdateTime = (SDL_GetPerformanceCounter() - currentTime) / static_cast<float>(performanceFrequency);

            if (elapsedUpdateTime < targetUpdateDuration)
            {
                Uint32 delayTime = static_cast<Uint32>((targetUpdateDuration - elapsedUpdateTime) * 1000.0f);
                SDL_Delay(delayTime);
            }
        }
    }

    return 0;
}

// SDL Application callbacks
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("TRPG", "0.1.3", "com.trpg");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    updatePreviousTime = SDL_GetTicks();
    renderPreviousTime = SDL_GetTicks();

    game = new Game();

    SDL_Thread* updateThread = SDL_CreateThread(
        UpdateThread, "UpdateThread", nullptr
    );
    
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;

        default:
            break;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    Uint64 currentTime = SDL_GetPerformanceCounter();
    float deltaTime = (currentTime - renderPreviousTime) / static_cast<float>(performanceFrequency);
    renderPreviousTime = currentTime;

    SetRenderDeltaTime(deltaTime);

    if (game->IsReady())
        game->Render(deltaTime);

    if (TARGET_FPS > 0)
    {
        float targetFrameDuration = 1.0f / TARGET_FPS;
        float elapsedFrameTime = (SDL_GetPerformanceCounter() - currentTime) / static_cast<float>(performanceFrequency);

        if (elapsedFrameTime < targetFrameDuration)
        {
            Uint32 delayTime = static_cast<Uint32>((targetFrameDuration - elapsedFrameTime) * 1000.0f);
            SDL_Delay(delayTime);
        }
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_Quit();
}
