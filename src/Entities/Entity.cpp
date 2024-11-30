#include "Entity.h"

#include <Config.h>

Entity::Entity(
    int id, Texture* texture, 
    const std::string& name, const std::string& type, 
    const std::string& category, 
    const Point& position, const Size& size, 
    const Collider& collider, 
    float speed
)
{
    this->id = id;
    this->texture = texture;
    this->name = name;
    this->type = type;
    this->category = category;
    this->position = position;
    this->size = size;
    this->collider = collider;
    this->speed = speed;

    this->collider.SetPosition(position);

    this->inventory = new Inventory(10);

    // Default characteristics
    this->health = 100;
    this->maxHealth = 100;

    this->mana = 100;
    this->maxMana = 100;

    this->level = 1;
    this->experience = 0;

    this->attack = 10;
    this->defense = 10;

    this->attackSpeed = 1;
    this->attackRange = 1;
}

Entity::~Entity()
{
    
}


int Entity::GetId() const
{
    return this->id;
}


Texture* Entity::GetTexture() const
{
    return this->texture;
}


std::string Entity::GetName() const
{
    return this->name;
}

std::string Entity::GetType() const
{
    return this->type;
}

std::string Entity::GetCategory() const
{
    return this->category;
}


Point Entity::GetPosition() const
{
    return this->position;
}

Size Entity::GetSize() const
{
    return this->size;
}

Point Entity::GetCenter() const
{
    return Point(
        this->position.x + this->size.width / 2,
        this->position.y + this->size.height / 2
    );
}


void Entity::SetPosition(const Point& position)
{
    this->position = position;

    this->collider.SetPosition(this->position);

    this->hasMovedLastTick = true;
}

void Entity::MoveBy(float dx, float dy)
{
    this->position.x += dx;
    this->position.y += dy;

    this->collider.SetPosition(this->position);

    this->hasMovedLastTick = true;
}


bool Entity::HasMovedLastTick() const
{
    return this->hasMovedLastTick;
}


Collider Entity::GetCollider() const
{
    return this->collider;
}

Point Entity::GetColliderCenter() const
{
    return this->collider.GetCenter();
}


bool Entity::CollidesWithEntities() const
{
    return this->collidesWithEntities;
}

bool Entity::CollidesWithWorldObjects() const
{
    return this->collidesWithWorldObjects;
}


bool Entity::CollidesWith(Collider other)
{
    return this->collider.CollidesWith(other);
}

bool Entity::CollidesWith(Entity* other)
{
    if (!this->collidesWithEntities)
        return false;

    return this->collider.CollidesWith(other->GetCollider());
}

bool Entity::CollidesWith(WorldObject* other)
{
    if (!this->collidesWithWorldObjects)
        return false;

    return this->collider.CollidesWith(other->GetCollider());
}


void Entity::OnCollision(Collider other)
{
    Point overlap = this->collider.GetCollisionOverlap(other);

    if (overlap.x < overlap.y)
    {
        if (this->position.x < other.x)
            this->MoveBy(-overlap.x, 0);

        else
            this->MoveBy(overlap.x, 0);
    }
    else
    {
        if (this->position.y < other.y)
            this->MoveBy(0, -overlap.y);

        else
            this->MoveBy(0, overlap.y);
    }

    // TODO: Remove if code above works as expected
    // Point colliderPosition = other->position;

    // float dx = this->position.x - colliderPosition.x;
    // float dy = this->position.y - colliderPosition.y;

    // float overlapX = (
    //     this->collider->size.width + 
    //     other->size.width
    // ) / 2 - abs(dx);
    
    // float overlapY = (
    //     this->collider->size.height + 
    //     other->size.height
    // ) / 2 - abs(dy);

    // if (overlapX < overlapY) {
    //     if (dx > 0)
    //         this->MoveBy(overlapX, 0);

    //     else
    //         this->MoveBy(-overlapX, 0);
    // }
    
    // else {
    //     if (dy > 0)
    //         this->MoveBy(0, overlapY);

    //     else
    //         this->MoveBy(0, -overlapY);
    // }
}

void Entity::OnCollision(Entity* other)
{
    this->OnCollision(other->GetCollider());
}

void Entity::OnCollision(WorldObject* other)
{
    this->OnCollision(other->GetCollider());
}


Inventory* Entity::GetInventory() const
{
    return this->inventory;
}


// Characteristics
float Entity::GetSpeed() const
{
    return this->speed;
}


float Entity::GetHealth() const
{
    return this->health;
}

float Entity::GetMaxHealth() const
{
    return this->maxHealth;
}


float Entity::GetMana() const
{
    return this->mana;
}

float Entity::GetMaxMana() const
{
    return this->maxMana;
}


float Entity::GetLevel() const
{
    return this->level;
}

float Entity::GetExperience() const
{
    return this->experience;
}


float Entity::GetAttack() const
{
    return this->attack;
}

float Entity::GetDefense() const
{
    return this->defense;
}


float Entity::GetAttackSpeed() const
{
    return this->attackSpeed;
}

float Entity::GetAttackRange() const
{
    return this->attackRange;
}


nlohmann::json Entity::Serialize() const
{
    nlohmann::json data;

    data["id"] = this->id;
    data["texture"] = this->texture->GetName();
    data["name"] = this->name;
    data["type"] = this->type;
    data["position"] = this->position.Serialize();
    data["size"] = this->size.Serialize();
    data["collider"] = this->collider.Serialize();
    
    data["inventory"] = this->inventory->Serialize();

    data["characteristics"]["speed"] = this->speed;
    data["characteristics"]["health"] = this->health;
    data["characteristics"]["maxHealth"] = this->maxHealth;
    data["characteristics"]["mana"] = this->mana;
    data["characteristics"]["maxMana"] = this->maxMana;
    data["characteristics"]["level"] = this->level;
    data["characteristics"]["experience"] = this->experience;
    data["characteristics"]["attack"] = this->attack;
    data["characteristics"]["defense"] = this->defense;
    data["characteristics"]["attackSpeed"] = this->attackSpeed;
    data["characteristics"]["attackRange"] = this->attackRange;

    data["collidesWithEntities"] = this->collidesWithEntities;
    data["collidesWithWorldObjects"] = this->collidesWithWorldObjects;

    return data;
}

Entity* Entity::FromJson(const nlohmann::json& data, Renderer* renderer)
{
    Entity* entity = new Entity(
        data["id"].get<int>(), 
        renderer->GetTexture(data["texture"].get<std::string>()), 
        data["name"].get<std::string>(), 
        data["type"].get<std::string>(), 
        data["category"].get<std::string>(), 
        Point::FromJson(data["position"]), 
        Size::FromJson(data["size"]), 
        Collider::FromJson(data["collider"]), 
        data["speed"].get<float>()
    );

    entity->inventory = Inventory::FromJson(data["inventory"], renderer);

    return entity;
}


void Entity::Update(float deltaTime)
{
    this->hasMovedLastTick = false;

    this->collider.SetPosition(this->position);
}


void Entity::Render(Renderer* renderer, float deltaTime)
{
    renderer->RenderTexture(this->texture, this->position, this->size);

    if (Config::SHOW_COLLIDERS)
    {
        renderer->RenderRect(
            this->collider.GetPosition(), 
            this->collider.GetSize(), 
            Config::COLLIDERS_COLOR
        );
    }
}
