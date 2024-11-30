#pragma once

#include <nlohmann/json.hpp>

#include "Point.h"
#include "Size.h"

class Collider
{
public:
    float x, y;
    float w, h;

    Collider(float x = 0, float y = 0, float w = 0, float h = 0);
    Collider(Point position, Size size);
    Collider(Size size);

    void SetPosition(float x, float y);
    void SetPosition(const Point& position);

    void SetSize(float width, float height);
    void SetSize(const Size& size);

    Point GetPosition() const;
    Size GetSize() const;
    Point GetCenter() const;

    bool IsEmpty() const;

    bool CollidesWith(const Collider& other) const;
    Point GetCollisionOverlap(const Collider& other) const;

    nlohmann::json Serialize() const;
    static Collider FromJson(const nlohmann::json& data);
};
