#include "GlobalFunctions.h"

#include <Windows.h>
#include <wtypes.h>
#include <Psapi.h>

#include <Game.h>


const bool* keyboardState;
std::unordered_set<int> usedIDs;

float renderDeltaTime = 0;
float updateDeltaTime = 0;


// Game
Renderer* GetRenderer()
{
    return Game::GetInstance()->GetRenderer();
}


// ID
std::unordered_set<int> GetUsedIDs()
{
    return usedIDs;
}

void SetUsedIDs(std::unordered_set<int> ids)
{
    usedIDs = ids;
}

void AddUsedID(int id)
{
    usedIDs.insert(id);
}

void RemoveUsedID(int id)
{
    usedIDs.erase(id);
}

int GenerateID()
{
    int id = rand() % 1000000;

    while (usedIDs.find(id) != usedIDs.end())
        id = rand() % 1000000;

    AddUsedID(id);

    return id;
}


// Time
float GetRenderDeltaTime()
{
    return renderDeltaTime;
}

float GetUpdateDeltaTime()
{
    return updateDeltaTime;
}


float GetFPS()
{
    return 1.0f / renderDeltaTime;
}

float GetUPS()
{
    return 1.0f / updateDeltaTime;
}


void SetRenderDeltaTime(float deltaTime)
{
    renderDeltaTime = deltaTime;
}

void SetUpdateDeltaTime(float deltaTime)
{
    updateDeltaTime = deltaTime;
}


// Keyboard and mouse
bool IsKeyPressed(int keyCode)
{
    if (!keyboardState)
        keyboardState = SDL_GetKeyboardState(NULL);

    return keyboardState[keyCode];
}

bool IsKeyPressed(std::string keyName)
{
    int keyCode = SDL_GetScancodeFromName(keyName.c_str());

    if (keyCode != SDL_SCANCODE_UNKNOWN)
        return IsKeyPressed(keyCode);

    return false;
}

bool IsMousePressed(MouseButton mouseButton)
{
    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_MASK(mouseButton);
}

Point GetMousePosition()
{
    float x, y;
    SDL_GetMouseState(&x, &y);

    return Point(x, y);
}


// Other
size_t GetMemoryUsage()
{
    PROCESS_MEMORY_COUNTERS_EX pmc;

    if (
        GetProcessMemoryInfo(
            GetCurrentProcess(), 
            (PROCESS_MEMORY_COUNTERS*)&pmc, 
            sizeof(pmc)
        )
    )
        return pmc.PrivateUsage / 1024;

    else
        return 0;
}

Size GetScreenSize()
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);

    return Size(desktop.right, desktop.bottom);
}


bool AreaContainsPoint(Point areaPosition, Size areaSize, Point point)
{
    return (
        point.x >= areaPosition.x &&
        point.x <= areaPosition.x + areaSize.width &&
        point.y >= areaPosition.y &&
        point.y <= areaPosition.y + areaSize.height
    );
}
