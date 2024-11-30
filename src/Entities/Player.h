#pragma once

#include "Entity.h"


class Player : public Entity
{
public:
    Player(
        int id, Texture* texture, 
        const std::string& name, 
        const Point& position, const Size& size, 
        const Collider& collider, 
        float speed
    );

    static Player* FromJson(const nlohmann::json& data, Renderer* renderer);

    void Update(float deltaTime) override;
};
