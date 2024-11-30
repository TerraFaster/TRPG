#include "Item.h"

Item::Item(
    Texture* texture, 
    const std::string& name, const std::string& type, 
    const std::string& category, 
    int count, int maxCount
)
{
    this->texture = texture;
    this->name = name;
    this->type = type;
    this->category = category;
    this->count = count;
    this->maxCount = maxCount;
}

Item::~Item()
{
    
}


Texture* Item::GetTexture() const
{
    return this->texture;
}


std::string Item::GetName() const
{
    return this->name;
}

std::string Item::GetType() const
{
    return this->type;
}

std::string Item::GetCategory() const
{
    return this->category;
}


int Item::GetCount() const
{
    return this->count;
}

int Item::GetMaxCount() const
{
    return this->maxCount;
}


void Item::AddCount(int count)
{
    this->count += count;
}

void Item::SetCount(int count)
{
    this->count = count;
}


void Item::Use()
{
    
}


nlohmann::json Item::Serialize() const
{
    return {
        {"texture", this->texture->GetName()}, 
        {"name", this->name}, 
        {"type", this->type}, 
        {"category", this->category}, 
        {"count", this->count}, 
        {"maxCount", this->maxCount}
    };
}

Item* Item::FromJson(const nlohmann::json& data, Renderer* renderer)
{
    return new Item(
        renderer->GetTexture(data["texture"].get<std::string>()), 
        data["name"].get<std::string>(), 
        data["type"].get<std::string>(), 
        data["category"].get<std::string>(), 
        data["count"].get<int>(), 
        data["maxCount"].get<int>()
    );
}
