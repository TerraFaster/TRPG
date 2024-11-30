#pragma once

#include <map>

#include "Item.h"


class Inventory
{
private:
    std::map<int, Item*> items;

    int size;
    int activeSlot = 0;

public:
    Inventory(int size);

    int GetSize();

    std::map<int, Item*> GetItems() const;
    Item* GetItem(int slot) const;
    Item* GetActiveItem() const;

    int GetActiveSlot() const;
    void SetActiveSlot(int slot);

    bool IsSlotEmpty(int slot) const;

    void AddItem(Item* item);
    void SetItem(int slot, Item* item);

    void MoveItem(int slotFrom, int slotTo);

    void RemoveItem(int slot);
    void RemoveItem(const std::string& type, int count);
    void RemoveItem(Item* item);

    void UseActiveItem() const;

    bool HasItem(const std::string& type) const;
    bool HasItem(const std::string& type, int count) const;

    nlohmann::json Serialize() const;
    static Inventory* FromJson(const nlohmann::json& data, Renderer* renderer);

    void Render(Renderer* renderer, float deltaTime);
};
