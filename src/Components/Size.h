#pragma once

#include <nlohmann/json.hpp>

class Size
{
public:
    float width, height;

    Size(float width = 0, float height = 0);

    void SetSize(float width, float height);

    nlohmann::json Serialize() const;
    static Size FromJson(const nlohmann::json& data);
};
