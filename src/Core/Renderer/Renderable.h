#pragma once

#include <Renderer.h>
#include <Point.h>

class Renderable
{
public:
    virtual ~Renderable() = default;

    virtual void Render(Renderer* renderer, float deltaTime) = 0;

    virtual Point GetPosition() const = 0;
};