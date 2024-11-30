#pragma once

#include <nlohmann/json.hpp>

#include <string>

#include <Texture.h>
#include <Point.h>
#include <Size.h>
#include <Renderer.h>


class Item
{
protected:
    Texture* texture;

    std::string name;
    std::string type;
    std::string category;

    int count;
    int maxCount;

public:
    Item(
        Texture* texture, 
        const std::string& name, const std::string& type, 
        const std::string& category, 
        int count, int maxCount
    );
    virtual ~Item();

    Texture* GetTexture() const;

    std::string GetName() const;
    std::string GetType() const;
    std::string GetCategory() const;

    int GetCount() const;
    int GetMaxCount() const;

    void AddCount(int count);
    void SetCount(int count);

    virtual void Use();

    nlohmann::json Serialize() const;
    static Item* FromJson(const nlohmann::json& data, Renderer* renderer);
};
