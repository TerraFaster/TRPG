#pragma once

#include <nlohmann/json.hpp>

#include <string>

#include <Texture.h>
#include <Point.h>
#include <Size.h>
#include <Collider.h>
#include <Renderer.h>
#include <Inventory.h>
#include <Renderable.h>
#include <WorldObject.h>

class Entity : public Renderable
{
protected:
    int id;

    Texture* texture;

    std::string name;
    std::string type;
    std::string category;

    Point position;
    Size size;

    Collider collider;

    Inventory* inventory;

    // Characteristics
    float speed;

    float health;
    float maxHealth;

    float mana;
    float maxMana;

    float level;
    float experience;

    float attack;
    float defense;

    float attackSpeed;
    float attackRange;

    bool collidesWithEntities = false;
    bool collidesWithWorldObjects = true;

    bool hasMovedLastTick = false;

public:
    Entity(
        int id, Texture* texture, 
        const std::string& name, const std::string& type, 
        const std::string& category, 
        const Point& position, const Size& size, 
        const Collider& collider, 
        float speed
    );
    virtual ~Entity();

    int GetId() const;

    Texture* GetTexture() const;

    std::string GetName() const;
    std::string GetType() const;
    std::string GetCategory() const;

    Point GetPosition() const override;
    Size GetSize() const;
    Point GetCenter() const;

    virtual void SetPosition(const Point& position);
    virtual void MoveBy(float dx, float dy);
    
    bool HasMovedLastTick() const;

    Collider GetCollider() const;
    Point GetColliderCenter() const;

    bool CollidesWithEntities() const;
    bool CollidesWithWorldObjects() const;

    bool CollidesWith(Collider other);
    bool CollidesWith(Entity* other);
    bool CollidesWith(WorldObject* other);

    virtual void OnCollision(Collider other);
    virtual void OnCollision(Entity* other);
    virtual void OnCollision(WorldObject* other);

    Inventory* GetInventory() const;

    // Characteristics
    float GetSpeed() const;

    float GetHealth() const;
    float GetMaxHealth() const;

    float GetMana() const;
    float GetMaxMana() const;

    float GetLevel() const;
    float GetExperience() const;

    float GetAttack() const;
    float GetDefense() const;

    float GetAttackSpeed() const;
    float GetAttackRange() const;

    nlohmann::json Serialize() const;
    static Entity* FromJson(const nlohmann::json& data, Renderer* renderer);

    virtual void Update(float deltaTime);
    virtual void Render(Renderer* renderer, float deltaTime) override;
};
