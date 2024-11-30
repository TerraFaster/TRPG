#include "GameGUI.h"

#include <GlobalFunctions.h>

#include <Size.h>


const int METRICS_UPDATE_DELAY = 10;


GameGUI::GameGUI()
{

}


void GameGUI::Render(Renderer* renderer, float deltaTime, Player* player)
{
    // Render selection
    Point mousePosition = renderer->ScreenToWorld(
        GetMousePosition()
    ) - Point(50, 50);

    mousePosition = Point(
        std::round(mousePosition.x / 100) * 100, 
        std::round(mousePosition.y / 100) * 100
    );

    renderer->RenderTexture(
        "selection", 
        mousePosition, 
        Size(100, 100)
    );

    // Render inventory
    player->GetInventory()->Render(renderer, deltaTime);

    // Render health bar
    renderer->RenderFilledRectAt(
        Point(10 - 3, 10 - 3), 
        Size(200 + 3 * 2, 15 + 3 * 2), 
        Color::Black
    );

    renderer->RenderGradientFilledRectAt(
        Point(10, 10), 
        Size(200 * player->GetHealth() / player->GetMaxHealth(), 15), 
        Color(130, 30, 45), 
        Color(180, 25, 50)
    );

    // Render mana bar
    renderer->RenderFilledRectAt(
        Point(10 - 3, 35 - 3), 
        Size(200 + 3 * 2, 15 + 3 * 2), 
        Color::Black
    );

    renderer->RenderGradientFilledRectAt(
        Point(10, 35), 
        Size(200 * player->GetMana() / player->GetMaxMana(), 15), 
        Color(0, 76, 151), 
        Color(14, 126, 236)
    );

    // Render metrics
    renderer->RenderText(
        (
            "FPS: " + std::to_string(fps) + 
            "\nUPS: " + std::to_string(ups) + 
            "\nMemory: " + std::to_string(GetMemoryUsage() / 1024) + "MB"
        ), 
        Point(10, 60), 
        "font", Color::White, 
        17
    );

    // Update metrics
    this->framesFromLastMetrics++;

    if (this->framesFromLastMetrics >= METRICS_UPDATE_DELAY)
    {
        this->framesFromLastMetrics = 0;

        this->fps = GetFPS();
        this->ups = GetUPS();
    }
}