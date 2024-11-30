#include "WorldObject.h"

#include <Config.h>


WorldObject::WorldObject(
    int id, Texture* texture, 
    const std::string& type, const std::string& category, 
    Point position, Size size, 
    Collider collider
)
{
    this->id = id;
    this->texture = texture;
    this->type = type;
    this->category = category;
    this->position = position;
    this->size = size;
    this->collider = collider;
}

WorldObject::~WorldObject()
{
    
}


int WorldObject::GetId() const
{
    return this->id;
}


Texture* WorldObject::GetTexture() const
{
    return this->texture;
}


Point WorldObject::GetPosition() const
{
    return this->position;
}

Size WorldObject::GetSize() const
{
    return this->size;
}

Point WorldObject::GetCenter() const
{
    return Point(
        this->position.x + this->size.width / 2,
        this->position.y + this->size.height / 2
    );
}


Collider WorldObject::GetCollider() const
{
    return this->collider;
}

Point WorldObject::GetColliderCenter() const
{
    return this->collider.GetCenter();
}


std::string WorldObject::GetType() const
{
    return this->type;
}

std::string WorldObject::GetCategory() const
{
    return this->category;
}


Rect WorldObject::GetVisibleRect() const
{
    return Rect(this->position - this->texture->GetOffset(), this->size);
}


void WorldObject::Interact()
{
    
}


bool WorldObject::IsDestroyed() const
{
    return false;
}


nlohmann::json WorldObject::Serialize()
{
    nlohmann::json data;

    data["id"] = this->id;
    data["texture"] = this->texture->GetName();
    data["type"] = this->type;
    data["category"] = this->category;
    data["position"] = this->position.Serialize();
    data["size"] = this->size.Serialize();
    data["collider"] = this->collider.Serialize();

    return data;
}

WorldObject* WorldObject::fromJson(const nlohmann::json& data, Renderer* renderer)
{
    return new WorldObject(
        data["id"].get<int>(), 
        renderer->GetTexture(data["texture"].get<std::string>()), 
        data["type"].get<std::string>(), 
        data["category"].get<std::string>(), 
        Point::FromJson(data["position"]), 
        Size::FromJson(data["size"]), 
        Collider::FromJson(data["collider"])
    );
}


Point WorldObject::GetRenderPosition() const
{
    return this->position;
}

Size WorldObject::GetRenderSize() const
{
    return this->size;
}

Texture* WorldObject::GetRenderTexture() const
{
    return this->texture;
}


void WorldObject::Update(float deltaTime)
{
    
}

void WorldObject::Render(Renderer* renderer, float deltaTime)
{
    renderer->RenderTexture(
        this->GetRenderTexture(), 
        this->GetRenderPosition(), 
        this->GetRenderSize()
    );

    if (Config::SHOW_COLLIDERS)
    {
        if (!this->collider.IsEmpty())
        {
            renderer->RenderRect(
                this->collider.GetPosition(), 
                this->collider.GetSize(), 
                Config::COLLIDERS_COLOR
            );
        }

        renderer->RenderRect(
            this->GetVisibleRect(), 
            Config::VISIBLE_RECT_COLOR
        );
    }
}
