#include "Size.h"

Size::Size(float width, float height)
{
    this->width = width;
    this->height = height;
}


void Size::SetSize(float width, float height)
{
    this->width = width;
    this->height = height;
}


nlohmann::json Size::Serialize() const
{
    return {
        { "width", this->width }, 
        { "height", this->height }
    };
}

Size Size::FromJson(const nlohmann::json& data)
{
    return Size(
        data["width"].get<float>(), 
        data["height"].get<float>()
    );
}
