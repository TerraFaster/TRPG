#pragma once

#include <nlohmann/json.hpp>

#include <vector>
#include <string>

#include <Point.h>
#include <WorldObject.h>
#include <Entity.h>
#include <Player.h>
#include <Renderer.h>

class World
{
private:
    std::vector<WorldObject*> tiles;
    std::vector<WorldObject*> objects;
    std::vector<Entity*> entities;

    std::vector<int> usedIDs;

public:
    World();

    std::vector<int> GetUsedIDs();

    void SetTile(WorldObject* tile);
    void SetTile(std::string type, Point tileGridPosition);
    void RemoveTile(Point tileGridPosition);
    WorldObject* GetTileAt(Point position);

    void AddObject(WorldObject* object);
    void AddObject(std::string type, Point position);
    void RemoveObject(WorldObject* object);

    std::vector<WorldObject*> GetObjects();
    std::vector<WorldObject*> GetObjectsAt(Point position);

    void AddEntity(Entity* entity);
    void AddEntity(std::string type, Point position);
    void RemoveEntity(Entity* entity);

    std::vector<Entity*> GetEntities();
    std::vector<Entity*> GetEntitiesAt(Point position);

    Player* GetPlayer();

    void Save(const std::string& path);
    static World* Load(const std::string& path, Renderer* renderer);

    void Update(float deltaTime);
    void Render(Renderer* renderer, float deltaTime);
};
