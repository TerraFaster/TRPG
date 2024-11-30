#pragma once

#include <string>

#include "GlobalFunctions.h"
#include <WorldObject.h>
#include <Entity.h>
#include <Item.h>


struct WorldObjectInfo
{
    std::string type;
    std::string category;
    std::string textureName;
    Size size;
    Size colliderSize;
};


struct EntityInfo
{
    std::string name;
    std::string category;
    std::string textureName;
    Size size;
    Size colliderSize;
    float speed;
};


struct ItemInfo
{
    std::string name;
    std::string category;
    std::string textureName;
    int maxCount;
};


// World object types
namespace TileType
{
    const std::string GRASS = "Tile_Grass";
    const std::string WATER = "Tile_Water";
}

namespace WorldObjectType
{
    const std::string ROCK = "WorldObject_Rock";
    const std::string TREE = "WorldObject_Tree";
    const std::string TREE_BIG = "WorldObject_TreeBig";
    const std::string BUSH = "WorldObject_Bush";
    const std::string SUNFLOWER = "WorldObject_Sunflower";
    const std::string LILYPAD = "WorldObject_Lilypad";
    const std::string WHEAT = "WorldObject_Wheat";
    const std::string TOMATO = "WorldObject_Tomato";
    const std::string HOUSE = "WorldObject_House";
}

namespace WorldObjectCategory
{
    const std::string TILE = "Category_WorldObject_Tile";
    const std::string OBJECT = "Category_WorldObject_Object";
    const std::string RESOURCE_OBJECT = "Category_WorldObject_ResourceObject";
}


// Entity types
namespace EntityType
{
    const std::string PLAYER = "Entity_Player";
    const std::string GOLEM = "Entity_Golem";
}

namespace EntityCategory
{
    const std::string PLAYER = "Category_Entity_Player";
    const std::string ENEMY = "Category_Entity_Enemy";
}


// Item types
namespace ItemType
{
    const std::string AXE = "Item_Axe";

    const std::string WOOD = "Item_Wood";
    const std::string STONE = "Item_Stone";

    const std::string WHEAT = "Item_Wheat";
    const std::string TOMATO = "Item_Tomato";
}

namespace ItemCategory
{
    const std::string TOOL = "Category_Item_Tool";
    const std::string RESOURCE = "Category_Item_Resource";
    const std::string FOOD = "Category_Item_Food";
}


// Factories
namespace Factory
{
    // WorldObjectInfo EmptyWorldObjectInfo;
    // EntityInfo EmptyEntityInfo ;
    // ItemInfo EmptyItemInfo;

    // const std::map<std::string, WorldObjectInfo> WorldObjectInfoMap;
    // const std::map<std::string, EntityInfo> EntityInfoMap;
    // const std::map<std::string, ItemInfo> ItemInfoMap;

    // DropTable rockDropTable;
    // DropTable treeDropTable;
    // DropTable bigTreeDropTable;

    // const std::map<std::string, ResourceWorldObjectInfo> ResourceWorldObjectInfoMap;

    WorldObjectInfo GetWorldObjectInfo(const std::string& type);
    EntityInfo GetEntityInfo(const std::string& type);
    ItemInfo GetItemInfo(const std::string& type);

    WorldObject* CreateWorldObject(const std::string& type, Point position);
    Entity* CreateEntity(const std::string& type, Point position, const std::string& name = "");
    Item* CreateItem(const std::string& type, int count);
}
