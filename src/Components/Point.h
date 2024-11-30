#pragma once

#include <nlohmann/json.hpp>

class Point
{
public:
    float x, y;

    Point(float x = 0, float y = 0);

    void SetPosition(float x, float y);
    void moveBy(float dx, float dy);

    float GetDistance(const Point& other) const;

    float GetDirection(const Point& other) const;
    float GetDirectionDegrees(const Point& other) const;

    nlohmann::json Serialize() const;
    static Point FromJson(const nlohmann::json& data);

    bool operator==(const Point& other) const;

    Point operator+(const Point& other) const;
    Point operator-(const Point& other) const;
    Point operator*(const Point& other) const;
    Point operator/(const Point& other) const;

    Point operator+(float value) const;
    Point operator-(float value) const;
    Point operator*(float value) const;
    Point operator/(float value) const;
};

