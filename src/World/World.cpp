#include <World.h>

#include <fstream>

#include <GlobalFunctions.h>
#include <Renderable.h>
#include <ResourceWorldObject.h>
#include <DropTable.h>
#include <GameTypes.h>


World::World()
{

}


std::vector<int> World::GetUsedIDs()
{
    return usedIDs;
}


void World::SetTile(WorldObject* tile)
{
    RemoveTile(tile->GetPosition() / 100);

    AddUsedID(tile->GetId());

    tiles.push_back(tile);
}

void World::SetTile(std::string type, Point tileGridPosition)
{
    Point test = tileGridPosition * 100;

    SetTile(Factory::CreateWorldObject(type, tileGridPosition * 100));
}

void World::RemoveTile(Point tileGridPosition)
{
    WorldObject* tile = GetTileAt(tileGridPosition);

    if (tile != nullptr)
    {
        RemoveUsedID(tile->GetId());
        tiles.erase(std::remove(tiles.begin(), tiles.end(), tile), tiles.end());
        delete tile;
    }
}

WorldObject* World::GetTileAt(Point tileGridPosition)
{
    tileGridPosition = tileGridPosition * 100;

    for (auto& tile : tiles)
    {
        if (tile->GetPosition() == tileGridPosition)
            return tile;
    }

    return nullptr;
}


void World::AddObject(WorldObject* object)
{
    AddUsedID(object->GetId());
    this->objects.push_back(object);
}

void World::AddObject(std::string type, Point position)
{
    this->AddObject(Factory::CreateWorldObject(type, position));
}

void World::RemoveObject(WorldObject* object)
{
    this->objects.erase(std::remove(this->objects.begin(), this->objects.end(), object), this->objects.end());
    RemoveUsedID(object->GetId());
    delete object;
}


std::vector<WorldObject*> World::GetObjects()
{
    return objects;
}

std::vector<WorldObject*> World::GetObjectsAt(Point position)
{
    std::vector<WorldObject*> objectsAtPosition;

    for (auto& object : objects)
    {
        Rect visibleRect = object->GetVisibleRect();

        if (visibleRect.Contains(position))
            objectsAtPosition.push_back(object);
    }

    return objectsAtPosition;
}


void World::AddEntity(Entity* entity)
{
    AddUsedID(entity->GetId());
    entities.push_back(entity);
}

void World::AddEntity(std::string type, Point position)
{
    AddEntity(Factory::CreateEntity(type, position));
}

void World::RemoveEntity(Entity* entity)
{
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
    RemoveUsedID(entity->GetId());
    delete entity;
}


std::vector<Entity*> World::GetEntities()
{
    return entities;
}

std::vector<Entity*> World::GetEntitiesAt(Point position)
{
    std::vector<Entity*> entitiesAtPosition;

    for (auto& entity : this->entities)
    {
        Point entityPosition = entity->GetPosition();
        Size entitySize = entity->GetSize();

        if (AreaContainsPoint(entityPosition, entitySize, position))
            entitiesAtPosition.push_back(entity);
    }

    return entitiesAtPosition;
}


Player* World::GetPlayer()
{
    for (auto& entity : this->entities)
    {
        if (entity->GetType() == EntityType::PLAYER)
            return (Player*)entity;
    }

    return nullptr;
}


void World::Save(const std::string& path)
{
    nlohmann::json data;

    // Serialize tiles
    for (auto& tile : this->tiles)
    {
        data["tiles"].push_back(tile->Serialize());
    }

    // Serialize objects
    for (auto& object : this->objects)
    {
        data["objects"].push_back(object->Serialize());
    }

    // Serialize entities
    for (auto& entity : this->entities)
    {
        data["entities"].push_back(entity->Serialize());
    }

    std::ofstream file(path);
    file << data.dump();
    file.close();
}

World* World::Load(const std::string& path, Renderer* renderer)
{
    World* world = new World();

    std::ifstream
    file(path);

    if (file.is_open())
    {
        nlohmann::json jsonData;
        file >> jsonData;

        // Load tiles
        for (auto& tileData : jsonData["tiles"])
        {
            WorldObject* tile = WorldObject::fromJson(tileData, renderer);
            world->SetTile(tile);
        }

        // Load objects
        for (auto& objectData : jsonData["objects"])
        {
            WorldObject* object = WorldObject::fromJson(objectData, renderer);
            world->AddObject(object);
        }

        // Load entities
        for (auto& entityData : jsonData["entities"])
        {
            if (jsonData["entities"]["type"] == EntityType::PLAYER)
            {
                Player* player = Player::FromJson(entityData, renderer);
                world->AddEntity(player);
            }
            else
            {
                Entity* entity = Entity::FromJson(entityData, renderer);
                world->AddEntity(entity);
            }
        }

        file.close();
    }

    return world;
}


void World::Update(float deltaTime)
{
    // Update objects
    for (auto& object : objects)
    {
        object->Update(deltaTime);

        if (object->IsDestroyed())
            RemoveObject(object);
    }

    // Update entities
    for (auto& entity : entities)
    {
        entity->Update(deltaTime);
    }

    // Check collisions of moved entities
    for (auto& entity : this->entities)
    {
        if (!entity->HasMovedLastTick())
            continue;

        // Check collisions with tiles
        for (auto& tile : this->tiles)
        {
            if (entity->CollidesWith(tile->GetCollider()))
                entity->OnCollision(tile);
        }

        // Check collisions with objects
        for (auto& object : this->objects)
        {
            if (entity->CollidesWith(object->GetCollider()))
                entity->OnCollision(object);
        }

        // Check collisions with other entities
        for (auto& otherEntity : this->entities)
        {
            if (entity == otherEntity)
                continue;

            if (entity->CollidesWith(otherEntity))
                entity->OnCollision(otherEntity);
        }
    }
}

void World::Render(Renderer* renderer, float deltaTime)
{
    // Draw tiles with water first
    for (auto& tile : tiles)
    {
        if (tile->GetTexture()->GetName() == "water")
            tile->Render(renderer, deltaTime);
    }

    for (auto& tile : tiles)
    {
        if (tile->GetTexture()->GetName() != "water")
            tile->Render(renderer, deltaTime);
    }

    // Collect objects and entities together for sorting
    std::vector<Renderable*> renderables;
    renderables.reserve(objects.size() + entities.size());

    for (auto& object : objects)
        renderables.push_back(object);

    for (auto& entity : entities)
        renderables.push_back(entity);

    // Sort by Y position
    std::sort(renderables.begin(), renderables.end(), [](Renderable* a, Renderable* b) {
        return a->GetPosition().y < b->GetPosition().y;
    });

    // Render sorted entities and objects
    for (auto& renderable : renderables)
        renderable->Render(renderer, deltaTime);
}
