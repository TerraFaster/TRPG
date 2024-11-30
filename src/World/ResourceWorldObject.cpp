#include <ResourceWorldObject.h>

#include <GameTypes.h>


ResourceWorldObject::ResourceWorldObject(
    int id, Texture* texture, 
    const std::string& type, 
    Point position, Size size, 
    Collider collider, 
    float health, float maxHealth, 
    DropTable dropTable
) : WorldObject(id, texture, type, WorldObjectCategory::RESOURCE_OBJECT, position, size, collider)
{
    this->health = health;
    this->maxHealth = maxHealth;
    this->dropTable = dropTable;
}


float ResourceWorldObject::GetHealth()
{
    return this->health;
}

float ResourceWorldObject::GetMaxHealth()
{
    return this->maxHealth;
}


DropTable ResourceWorldObject::GetDropTable() const
{
    return this->dropTable;
}


void ResourceWorldObject::Damage(float amount)
{
    this->health -= amount;

    if (this->health < 0)
        this->health = 0;
    
    shakeFramesRemaining = 15;
}


bool ResourceWorldObject::IsDestroyed() const
{
    return this->health <= 0;
}


nlohmann::json ResourceWorldObject::Serialize()
{
    nlohmann::json data = WorldObject::Serialize();

    data["health"] = this->health;
    data["maxHealth"] = this->maxHealth;
    data["dropTable"] = this->dropTable.Serialize();

    return data;
}


ResourceWorldObject* ResourceWorldObject::fromJson(const nlohmann::json& data, Renderer* renderer)
{
    return new ResourceWorldObject(
        data["id"].get<int>(), 
        renderer->GetTexture(data["texture"].get<std::string>()), 
        data["type"].get<std::string>(), 
        Point::FromJson(data["position"]), 
        Size::FromJson(data["size"]), 
        Collider::FromJson(data["collider"]), 
        data["health"].get<float>(), 
        data["maxHealth"].get<float>(), 
        DropTable::FromJson(data["dropTable"])
    );
}


Point ResourceWorldObject::GetRenderPosition() const
{
    Point renderPosition = this->position;

    if (this->shakeFramesRemaining > 0)
    {
        renderPosition.x += (std::rand() % 11 - 5);
        renderPosition.y += (std::rand() % 11 - 5);
    }

    return renderPosition;
}


void ResourceWorldObject::Update(float deltaTime)
{
    WorldObject::Update(deltaTime);
}

void ResourceWorldObject::Render(Renderer* renderer, float deltaTime)
{
    WorldObject::Render(renderer, deltaTime);

    // Render health bar
    if (this->health < this->maxHealth)
    {
        Rect visibleRect = this->GetVisibleRect();
        Point healtBarPosition = visibleRect.GetBottomLeft() + Point(visibleRect.width / 4, 5);

        renderer->RenderFilledRect(
            healtBarPosition - Point(3, 3), 
            Size(visibleRect.width / 2 + 6, 16), 
            Color::Black
        );

        renderer->RenderGradientFilledRect(
            healtBarPosition, 
            Size(visibleRect.width / 2 * (this->health / this->maxHealth), 10), 
            Color(130, 30, 45), 
            Color(180, 25, 50)
        );
    }

    if (this->shakeFramesRemaining > 0)
        this->shakeFramesRemaining--;
}
