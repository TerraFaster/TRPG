#include "Inventory.h"


const Size INVENTORY_SLOT_SIZE = Size(65, 65);
const Size ITEM_SIZE = Size(40, 40);


Inventory::Inventory(int size)
{
    this->size = size;
}


int Inventory::GetSize()
{
    return this->size;
}


std::map<int, Item*> Inventory::GetItems() const
{
    return this->items;
}

Item* Inventory::GetItem(int slot) const
{
    return this->items.at(slot);
}

Item* Inventory::GetActiveItem() const
{
    return this->items.at(this->activeSlot);
}


int Inventory::GetActiveSlot() const
{
    return this->activeSlot;
}

void Inventory::SetActiveSlot(int slot)
{
    this->activeSlot = slot;
}

bool Inventory::IsSlotEmpty(int slot) const
{
    return this->items.find(slot) == this->items.end();
}


void Inventory::AddItem(Item* item)
{
    for (int i = 0; i < this->size; i++)
    {
        if (!this->IsSlotEmpty(i))
        {
            Item* existingItem = this->items[i];

            if (existingItem->GetType() == item->GetType())
            {
                if (existingItem->GetCount() + item->GetCount() <= existingItem->GetMaxCount())
                {
                    existingItem->AddCount(item->GetCount());
                    return;
                }
            }
        }
        else
        {
            this->items[i] = item;
            return;
        }
    }
}

void Inventory::SetItem(int slot, Item* item)
{
    this->items[slot] = item;
}


void Inventory::MoveItem(int slotFrom, int slotTo)
{
    Item* item = this->items[slotFrom];

    this->items.erase(slotFrom);
    this->items[slotTo] = item;
}


void Inventory::RemoveItem(int slot)
{
    this->items.erase(slot);
}

void Inventory::RemoveItem(const std::string& type, int count)
{
    for (auto& item : this->items)
    {
        if (item.second->GetType() == type)
        {
            if (item.second->GetCount() > count)
            {
                item.second->SetCount(item.second->GetCount() - count);
                break;
            }
            else
            {
                this->items.erase(item.first);
                break;
            }
        }
    }
}

void Inventory::RemoveItem(Item* item)
{
    for (auto& i : this->items)
    {
        if (i.second->GetType() == item->GetType())
        {
            if (i.second->GetCount() > item->GetCount())
            {
                i.second->SetCount(i.second->GetCount() - item->GetCount());
                break;
            }
            else
            {
                this->items.erase(i.first);
                break;
            }
        }
    }
}


void Inventory::UseActiveItem() const
{
    this->items.at(this->activeSlot)->Use();
}


bool Inventory::HasItem(const std::string& type) const
{
    for (auto& item : this->items)
    {
        if (item.second->GetType() == type)
            return true;
    }

    return false;
}

bool Inventory::HasItem(const std::string& type, int count) const
{
    for (auto& item : this->items)
    {
        if (item.second->GetType() == type && item.second->GetCount() >= count)
            return true;
    }

    return false;
}


nlohmann::json Inventory::Serialize() const
{
    nlohmann::json data;

    data["size"] = this->size;
    data["activeSlot"] = this->activeSlot;

    nlohmann::json items;
    for (auto& item : this->items)
    {
        items[std::to_string(item.first)] = item.second->Serialize();
    }
    data["items"] = items;

    return data;
}

Inventory* Inventory::FromJson(const nlohmann::json& data, Renderer* renderer)
{
    Inventory* inventory = new Inventory(data["size"]);

    inventory->activeSlot = data["activeSlot"];

    for (auto& item : data["items"].items())
    {
        inventory->items[std::stoi(item.key())] = Item::FromJson(item.value(), renderer);
    }

    return inventory;
}


void Inventory::Render(Renderer* renderer, float deltaTime)
{
    // Draw Inventory at the bottom center of the screen
    Point inventoryPosition = Point(
        renderer->GetSize().width / 2 - this->size * INVENTORY_SLOT_SIZE.width / 2, 
        renderer->GetSize().height - INVENTORY_SLOT_SIZE.height - 5
    );

    for (int i = 0; i < this->size; i++)
    {
        renderer->RenderTextureAt(
            "inventory_slot", 
            inventoryPosition + Point(i * INVENTORY_SLOT_SIZE.width + i, 0), 
            INVENTORY_SLOT_SIZE
        );
    }

    for (int i = 0; i < this->size; i++)
    {
        if (this->IsSlotEmpty(i))
            continue;

        Item* item = this->items[i];

        renderer->RenderTextureAt(
            item->GetTexture(), 
            inventoryPosition + Point(
                i * INVENTORY_SLOT_SIZE.width + i + (INVENTORY_SLOT_SIZE.width - ITEM_SIZE.width) / 2, 
                (INVENTORY_SLOT_SIZE.height - ITEM_SIZE.height) / 2
            ), 
            ITEM_SIZE
        );

        renderer->RenderText(
            std::to_string(item->GetCount()), 
            inventoryPosition + Point(
                i * INVENTORY_SLOT_SIZE.width + i + INVENTORY_SLOT_SIZE.width / 2 - 10, 
                INVENTORY_SLOT_SIZE.height - 17
            ),
            "font", Color::White, 
            22
        );
    }
}
