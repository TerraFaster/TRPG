#pragma once

#include <nlohmann/json.hpp>

#include <vector>
#include <unordered_map>

#include "WorldObject.h"
#include <DropTable.h>


class ResourceWorldObject : public WorldObject
{
private:
    float health;
    float maxHealth;

    DropTable dropTable;

    int shakeFramesRemaining = 0;

public:
    ResourceWorldObject(
        int id, Texture* texture, 
        const std::string& type, 
        Point position, Size size, 
        Collider collider, 
        float health, float maxHealth, 
        DropTable dropTable
    );

    float GetHealth();
    float GetMaxHealth();

    DropTable GetDropTable() const;

    void Damage(float amount);

    bool IsDestroyed() const override;

    nlohmann::json Serialize();
    static ResourceWorldObject* fromJson(const nlohmann::json& data, Renderer* renderer);

    Point GetRenderPosition() const override;

    void Update(float deltaTime) override;
    void Render(Renderer* renderer, float deltaTime) override;
};
