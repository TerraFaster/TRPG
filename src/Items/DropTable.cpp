#include "DropTable.h"


// DropEntry
DropEntry::DropEntry(const std::string& itemType, const FixedCountDrop& fixedDrop)
{
    this->itemType = itemType;
    this->isFixedDrop = true;
    this->fixedCountDrop = fixedDrop;
}

DropEntry::DropEntry(const std::string& itemType, const std::vector<ProbabilityCountDrop>& probDrops)
{
    this->itemType = itemType;
    this->isFixedDrop = false;
    this->probCountDrops = probDrops;
}


std::string DropEntry::GetItemType() const
{
    return this->itemType;
}

bool DropEntry::IsFixedDrop() const
{
    return this->isFixedDrop;
}

int DropEntry::GetDropCount() const
{
    std::random_device rd;
    std::mt19937 gen(rd());

    // Fixed min-max count
    if (this->isFixedDrop)
    {
        std::uniform_int_distribution<> dist(this->fixedCountDrop.minCount, this->fixedCountDrop.maxCount);
        return dist(gen);
    }
    // Probability-based drop
    else
    {
        for (const auto& probDrop : this->probCountDrops)
        {
            std::uniform_int_distribution<> chanceDist(1, 100);

            if (chanceDist(gen) <= probDrop.chance)
            {
                std::uniform_int_distribution<> countDist(probDrop.minCount, probDrop.maxCount);
                return countDist(gen);
            }
        }

        // No drop if no chance was met
        return 0;
    }
}


nlohmann::json DropEntry::Serialize() const
{
    nlohmann::json data;

    data["itemType"] = this->itemType;
    data["isFixedDrop"] = this->isFixedDrop;

    if (this->isFixedDrop)
    {
        data["minCount"] = this->fixedCountDrop.minCount;
        data["maxCount"] = this->fixedCountDrop.maxCount;
    }
    else
    {
        nlohmann::json probDrops;

        for (const auto& probDrop : this->probCountDrops)
        {
            nlohmann::json probDropData;
            probDropData["minCount"] = probDrop.minCount;
            probDropData["maxCount"] = probDrop.maxCount;
            probDropData["chance"] = probDrop.chance;

            probDrops.push_back(probDropData);
        }

        data["probCountDrops"] = probDrops;
    }

    return data;
}

DropEntry DropEntry::FromJson(const nlohmann::json& data)
{
    std::string itemType = data["itemType"].get<std::string>();
    bool isFixedDrop = data["isFixedDrop"].get<bool>();

    if (isFixedDrop)
    {
        FixedCountDrop fixedDrop = { data["minCount"].get<int>(), data["maxCount"].get<int>() };
        return DropEntry(itemType, fixedDrop);
    }
    else
    {
        std::vector<ProbabilityCountDrop> probDrops;

        for (const auto& probDropData : data["probCountDrops"])
        {
            ProbabilityCountDrop probDrop = { probDropData["minCount"].get<int>(), probDropData["maxCount"].get<int>(), probDropData["chance"].get<int>() };
            probDrops.push_back(probDrop);
        }

        return DropEntry(itemType, probDrops);
    }
}



// DropTable
DropTable::DropTable()
{
    this->entries = std::vector<DropEntry>();
}

DropTable::~DropTable()
{

}


DropTable DropTable::AddFixedDrop(const std::vector<std::string>& itemTypes, int minCount, int maxCount)
{
    FixedCountDrop fixedDrop = { minCount, maxCount };

    for (const auto& item : itemTypes)
        this->entries.emplace_back(item, fixedDrop);

    return *this;
}

DropTable DropTable::AddProbabilityDrop(const std::vector<std::string>& itemTypes, const std::map<std::pair<int, int>, int>& probMap)
{
    for (const auto& item : itemTypes)
    {
        std::vector<ProbabilityCountDrop> probDrops;

        for (const auto& [countRange, chance] : probMap)
            probDrops.push_back({ countRange.first, countRange.second, chance });

        entries.emplace_back(item, probDrops);
    }

    return *this;
}


std::vector<Item*> DropTable::GenerateDrops() const
{
    std::vector<Item*> droppedItems;

    for (const auto& entry : entries)
    {
        int count = entry.GetDropCount();

        ItemInfo itemInfo = Factory::GetItemInfo(entry.GetItemType());

        if (itemInfo.maxCount == -1)
            continue;

        while (count > 0)
        {
            int dropCount = std::min(count, itemInfo.maxCount);

            Item* item = Factory::CreateItem(entry.GetItemType(), dropCount);
            droppedItems.push_back(item);

            count -= dropCount;
        }
    }

    return droppedItems;
}


nlohmann::json DropTable::Serialize() const
{
    nlohmann::json data;

    for (const auto& entry : this->entries)
        data.push_back(entry.Serialize());

    return data;
}

DropTable DropTable::FromJson(const nlohmann::json& data)
{
    DropTable dropTable;

    for (const auto& entryData : data)
        dropTable.entries.push_back(DropEntry::FromJson(entryData));

    return dropTable;
}
