#include "Point.h"

#define _USE_MATH_DEFINES
#include <math.h>

Point::Point(float x, float y)
{
    this->x = x;
    this->y = y;
}


void Point::SetPosition(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Point::moveBy(float dx, float dy)
{
    this->x += dx;
    this->y += dy;
}


float Point::GetDistance(const Point& other) const
{
    return sqrt(
        pow(other.x - this->x, 2) + pow(other.y - this->y, 2)
    );
}


float Point::GetDirection(const Point& other) const
{
    return atan2(other.y - this->y, other.x - this->x);
}

float Point::GetDirectionDegrees(const Point& other) const
{
    return GetDirection(other) * 180 / M_PI;
}


nlohmann::json Point::Serialize() const
{
    return {
        {"x", this->x}, 
        {"y", this->y}
    };
}

Point Point::FromJson(const nlohmann::json& data)
{
    return Point(
        data["x"].get<float>(), 
        data["y"].get<float>()
    );
}


bool Point::operator==(const Point& other) const
{
    return this->x == other.x && this->y == other.y;
}


Point Point::operator+(const Point& other) const
{
    return Point(
        this->x + other.x, 
        this->y + other.y
    );
}

Point Point::operator-(const Point& other) const
{
    return Point(
        this->x - other.x, 
        this->y - other.y
    );
}

Point Point::operator*(const Point& other) const
{
    return Point(
        this->x * other.x, 
        this->y * other.y
    );
}

Point Point::operator/(const Point& other) const
{
    return Point(
        this->x / other.x, 
        this->y / other.y
    );
}


Point Point::operator+(float value) const
{
    return Point(
        this->x + value, 
        this->y + value
    );
}

Point Point::operator-(float value) const
{
    return Point(
        this->x - value, 
        this->y - value
    );
}

Point Point::operator*(float value) const
{
    return Point(
        this->x * value, 
        this->y * value
    );
}

Point Point::operator/(float value) const
{
    return Point(
        this->x / value, 
        this->y / value
    );
}
