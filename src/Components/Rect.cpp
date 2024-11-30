#include "Rect.h"


Rect::Rect(float x, float y, float width, float height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

Rect::Rect(Point position, Size size)
{
    this->x = position.x;
    this->y = position.y;
    this->width = size.width;
    this->height = size.height;
}

Rect::~Rect()
{
    
}

Point Rect::GetPosition() const
{
    return Point(this->x, this->y);
}

Size Rect::GetSize() const
{
    return Size(this->width, this->height);
}

Point Rect::GetCenter() const
{
    return Point(this->x + this->width / 2, this->y + this->height / 2);
}


Point Rect::GetTopLeft() const
{
    return Point(this->x, this->y);
}

Point Rect::GetTopRight() const
{
    return Point(this->x + this->width, this->y);
}

Point Rect::GetBottomLeft() const
{
    return Point(this->x, this->y + this->height);
}

Point Rect::GetBottomRight() const
{
    return Point(this->x + this->width, this->y + this->height);
}


bool Rect::Contains(Point point)
{
    return point.x >= this->x && point.x <= this->x + this->width &&
           point.y >= this->y && point.y <= this->y + this->height;
}

bool Rect::Intersects(Rect other)
{
    return this->x < other.x + other.width &&
           this->x + this->width > other.x &&
           this->y < other.y + other.height &&
           this->y + this->height > other.y;
}
