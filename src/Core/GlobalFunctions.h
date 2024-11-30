#pragma once

#include <unordered_set>
#include <string>

#include <Point.h>
#include <Size.h>
#include <Renderer.h>


enum MouseButton {
    LEFT = 1,
    MIDDLE = 2,
    RIGHT = 3
};


// Game
Renderer* GetRenderer();


// ID
std::unordered_set<int> GetUsedIDs();
void SetUsedIDs(std::unordered_set<int> ids);
void AddUsedID(int id);
void RemoveUsedID(int id);
int GenerateID();

// Time
float GetRenderDeltaTime();
float GetUpdateDeltaTime();

float GetFPS();
float GetUPS();

void SetRenderDeltaTime(float deltaTime);
void SetUpdateDeltaTime(float deltaTime);

// Keyboard and mouse
bool IsKeyPressed(int keyCode);
bool IsKeyPressed(std::string keyName);

bool IsMousePressed(MouseButton button);

Point GetMousePosition();

// Other
size_t GetMemoryUsage();
Size GetScreenSize();

bool AreaContainsPoint(Point areaPosition, Size areaSize, Point point);
