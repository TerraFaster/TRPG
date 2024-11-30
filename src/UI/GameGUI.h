#pragma once

#include <Renderer.h>
#include <Player.h>


class GameGUI
{
private:
    int fps = 0;
    int ups = 0;

    int framesFromLastMetrics = 0;

public:
    GameGUI();

    void Render(Renderer* renderer, float deltaTime, Player* player);
};
