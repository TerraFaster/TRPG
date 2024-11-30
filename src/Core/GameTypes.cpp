#include "GameTypes.h"

#include <ResourceWorldObject.h>
#include <Player.h>
#include <DropTable.h>


struct ResourceWorldObjectInfo
{
    int maxHealth;
    DropTable dropTable;
};


WorldObjectInfo EmptyWorldObjectInfo = { "", "", "", { 0, 0 }, { 0, 0 } };
EntityInfo EmptyEntityInfo = { "", "", "", { 0, 0 }, { 0, 0 }, 0 };
ItemInfo EmptyItemInfo = { "", "", "", -1 };


const std::map<std::string, WorldObjectInfo> WorldObjectInfoMap = {
    { TileType::GRASS, { TileType::GRASS, WorldObjectCategory::TILE, "grass", Size(100, 125), Size(0, 0) } }, 
    { TileType::WATER, { TileType::WATER, WorldObjectCategory::TILE, "water", Size(100, 100), Size(100, 100) } }, 
    { WorldObjectType::ROCK, { WorldObjectType::ROCK, WorldObjectCategory::RESOURCE_OBJECT, "rock", Size(100, 100), Size(100, 100) } }, 
    { WorldObjectType::TREE, { WorldObjectType::TREE, WorldObjectCategory::RESOURCE_OBJECT, "tree", Size(100, 200), Size(100, 100) } }, 
    { WorldObjectType::TREE_BIG, { WorldObjectType::TREE_BIG, WorldObjectCategory::RESOURCE_OBJECT, "tree_big", Size(200, 250), Size(100, 100) } }, 
    { WorldObjectType::BUSH, { WorldObjectType::BUSH, WorldObjectCategory::OBJECT, "bush", Size(100, 100), Size(0, 0) } }, 
    { WorldObjectType::SUNFLOWER, { WorldObjectType::SUNFLOWER, WorldObjectCategory::OBJECT, "sunflower", Size(75, 150), Size(0, 0) } }, 
    { WorldObjectType::LILYPAD, { WorldObjectType::LILYPAD, WorldObjectCategory::OBJECT, "lilypad", Size(75, 75), Size(0, 0) } }, 
    { WorldObjectType::WHEAT, { WorldObjectType::WHEAT, WorldObjectCategory::OBJECT, "wheat", Size(75, 75), Size(0, 0) } }, 
    { WorldObjectType::TOMATO, { WorldObjectType::TOMATO, WorldObjectCategory::OBJECT, "tomato", Size(75, 75), Size(0, 0) } }
};

const std::map<std::string, EntityInfo> EntityInfoMap = {
    { EntityType::PLAYER, { "Player", EntityCategory::PLAYER, "player", Size(80, 80), Size(80, 80), 400 } }, 
    { EntityType::GOLEM, { "Golem", EntityCategory::ENEMY, "golem", Size(80, 80), Size(80, 80), 300 } }
};

const std::map<std::string, ItemInfo> ItemInfoMap = {
    { ItemType::AXE, { "Axe", ItemCategory::TOOL, "axe_item", 1 } }, 
    { ItemType::WOOD, { "Wood", ItemCategory::RESOURCE, "wood_item", 64 } }, 
    { ItemType::STONE, { "Stone", ItemCategory::RESOURCE, "rock_item", 64 } }, 
    { ItemType::WHEAT, { "Wheat", ItemCategory::FOOD, "wheat_item", 64 } }, 
    { ItemType::TOMATO, { "Tomato", ItemCategory::FOOD, "tomato_item", 64 } }
};


// Drop tables
DropTable rockDropTable = DropTable()
    .AddFixedDrop({ ItemType::STONE }, 1, 2);

DropTable treeDropTable = DropTable()
    .AddFixedDrop({ ItemType::WOOD }, 1, 2);

DropTable bigTreeDropTable = DropTable()
    .AddFixedDrop({ ItemType::WOOD }, 2, 4);

const std::map<std::string, ResourceWorldObjectInfo> ResourceWorldObjectInfoMap = {
    { WorldObjectType::ROCK, { 200, rockDropTable } }, 
    { WorldObjectType::TREE, { 200, treeDropTable } }, 
    { WorldObjectType::TREE_BIG, { 400, bigTreeDropTable } }
};


WorldObjectInfo Factory::GetWorldObjectInfo(const std::string& type)
{
    if (WorldObjectInfoMap.find(type) != WorldObjectInfoMap.end())
        return WorldObjectInfoMap.at(type);

    return EmptyWorldObjectInfo;
}

EntityInfo Factory::GetEntityInfo(const std::string& type)
{
    if (EntityInfoMap.find(type) != EntityInfoMap.end())
        return EntityInfoMap.at(type);

    return EmptyEntityInfo;
}

ItemInfo Factory::GetItemInfo(const std::string& type)
{
    if (ItemInfoMap.find(type) != ItemInfoMap.end())
        return ItemInfoMap.at(type);

    return EmptyItemInfo;
}


WorldObject* Factory::CreateWorldObject(const std::string& type, Point position)
{
    WorldObject* object = nullptr;

    if (WorldObjectInfoMap.find(type) != WorldObjectInfoMap.end())
    {
        WorldObjectInfo objectInfo = WorldObjectInfoMap.at(type);

        if (objectInfo.category == WorldObjectCategory::RESOURCE_OBJECT)
        {            
            ResourceWorldObjectInfo resourceObjectInfo = ResourceWorldObjectInfoMap.at(type);

            object = new ResourceWorldObject(
                GenerateID(), 
                GetRenderer()->GetTexture(objectInfo.textureName), 
                type, 
                position, objectInfo.size, 
                Collider(position, objectInfo.colliderSize), 
                resourceObjectInfo.maxHealth, 
                resourceObjectInfo.maxHealth, 
                resourceObjectInfo.dropTable
            );
        }
        else
        {
            object = new WorldObject(
                GenerateID(), 
                GetRenderer()->GetTexture(objectInfo.textureName), 
                type, objectInfo.category, 
                position, objectInfo.size, 
                Collider(position, objectInfo.colliderSize)
            );
        }
    }

    return object;
}

Entity* Factory::CreateEntity(const std::string& type, Point position, const std::string& name)
{
    Entity* entity = nullptr;

    if (EntityInfoMap.find(type) != EntityInfoMap.end())
    {
        EntityInfo entityInfo = EntityInfoMap.at(type);

        if (type == EntityType::PLAYER)
        {
            entity = new Player(
                GenerateID(), 
                GetRenderer()->GetTexture(entityInfo.textureName), 
                (name.empty() ? name : entityInfo.name), 
                position, entityInfo.size, 
                Collider(position, entityInfo.colliderSize), 
                entityInfo.speed
            );
        }
        else
        {
            entity = new Entity(
                GenerateID(), 
                GetRenderer()->GetTexture(entityInfo.textureName), 
                (name.empty() ? name : entityInfo.name), type, 
                entityInfo.category, 
                position, entityInfo.size, 
                Collider(position, entityInfo.colliderSize), 
                entityInfo.speed
            );
        }
    }

    return entity;
}

Item* Factory::CreateItem(const std::string& type, int count)
{
    Item* item = nullptr;

    if (ItemInfoMap.find(type) != ItemInfoMap.end())
    {
        ItemInfo itemInfo = ItemInfoMap.at(type);

        item = new Item(
            GetRenderer()->GetTexture(itemInfo.textureName), 
            itemInfo.name, type, 
            itemInfo.category, 
            count, itemInfo.maxCount
        );
    }

    return item;
}
