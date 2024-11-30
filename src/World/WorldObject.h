#pragma once

#include <nlohmann/json.hpp>

#include <Point.h>
#include <Size.h>
#include <Rect.h>
#include <Collider.h>
#include <Renderer.h>
#include <Renderable.h>


class WorldObject : public Renderable
{
protected:
    int id;

    Texture* texture;

    std::string type;
    std::string category;

    Point position;
    Size size;
    Collider collider;

public:
    WorldObject(
        int id, Texture* texture, 
        const std::string& type, const std::string& category, 
        Point position, Size size, 
        Collider collider
    );
    ~WorldObject();

    int GetId() const;

    Texture* GetTexture() const;

    Point GetPosition() const override;
    Size GetSize() const;
    Point GetCenter() const;

    Collider GetCollider() const;
    Point GetColliderCenter() const;

    std::string GetType() const;
    std::string GetCategory() const;

    virtual Rect GetVisibleRect() const;

    virtual void Interact();

    virtual bool IsDestroyed() const;

    nlohmann::json Serialize();
    static WorldObject* fromJson(const nlohmann::json& data, Renderer* renderer);

    virtual Point GetRenderPosition() const;
    virtual Size GetRenderSize() const;
    virtual Texture* GetRenderTexture() const;

    virtual void Update(float deltaTime);
    virtual void Render(Renderer* renderer, float deltaTime) override;
};
