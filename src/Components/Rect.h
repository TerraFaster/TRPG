#pragma once

#include <Point.h>
#include <Size.h>

class Rect
{
public:
    float x;
    float y;
    float width;
    float height;

    Rect(float x = 0, float y = 0, float width = 0, float height = 0);
    Rect(Point position, Size size);
    ~Rect();

    Point GetPosition() const;
    Size GetSize() const;
    Point GetCenter() const;

    Point GetTopLeft() const;
    Point GetTopRight() const;
    Point GetBottomLeft() const;
    Point GetBottomRight() const;

    bool Contains(Point point);
    bool Intersects(Rect other);
};
