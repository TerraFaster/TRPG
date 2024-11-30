#include "Player.h"

#include <GlobalFunctions.h>
#include <GameTypes.h>


Player::Player(
    int id, Texture* texture, 
    const std::string& name, 
    const Point& position, const Size& size, 
    const Collider& collider, 
    float speed
) : Entity(id, texture, name, EntityType::PLAYER, EntityCategory::PLAYER, position, size, collider, speed)
{

}

Player* Player::FromJson(const nlohmann::json& data, Renderer* renderer)
{
    Player* player = static_cast<Player*>(Entity::FromJson(data, renderer));

    return player;

    // TODO: Remove if code above works as expected
    // return new Player(
    //     data["id"].get<int>(), 
    //     renderer->GetTexture(data["texture"].get<std::string>()), 
    //     data["name"].get<std::string>(), 
    //     Point::FromJson(data["position"]), 
    //     Size::FromJson(data["size"]), 
    //     Collider::FromJson(data["collider"]), 
    //     data["speed"].get<float>()
    // );
}


void Player::Update(float deltaTime)
{
    Entity::Update(deltaTime);

    float speed = this->GetSpeed();

    if (IsKeyPressed("W"))
        this->MoveBy(0, -speed * deltaTime);

    if (IsKeyPressed("S"))
        this->MoveBy(0, speed * deltaTime);

    if (IsKeyPressed("A"))
        this->MoveBy(-speed * deltaTime, 0);

    if (IsKeyPressed("D"))
        this->MoveBy(speed * deltaTime, 0);
}
