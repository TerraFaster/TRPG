#pragma once

#include <nlohmann/json.hpp>

#include <vector>
#include <unordered_map>
#include <random>

#include "Item.h"
#include <GameTypes.h>


// `int` minCount - minimum number of items to drop
// `int` maxCount - maximum number of items to drop
struct FixedCountDrop
{
    int minCount;
    int maxCount;
};


// `int` minCount - minimum number of items to drop
// `int` maxCount - maximum number of items to drop
// `int` chance - 0 to 100 chance of dropping this count
struct ProbabilityCountDrop
{
    int minCount;
    int maxCount;
    int chance;
};


class DropEntry
{
private:
    std::string itemType;
    bool isFixedDrop;

    FixedCountDrop fixedCountDrop;
    std::vector<ProbabilityCountDrop> probCountDrops;

public:
    DropEntry(const std::string& itemType, const FixedCountDrop& fixedDrop);
    DropEntry(const std::string& itemType, const std::vector<ProbabilityCountDrop>& probDrops);
    
    std::string GetItemType() const;

    bool IsFixedDrop() const;

    int GetDropCount() const;

    nlohmann::json Serialize() const;
    static DropEntry FromJson(const nlohmann::json& data);
};


class DropTable
{
private:
    std::vector<DropEntry> entries;

public:
    DropTable();
    ~DropTable();

    DropTable AddFixedDrop(const std::vector<std::string>& itemTypes, int minCount, int maxCount);
    DropTable AddProbabilityDrop(const std::vector<std::string>& itemTypes, const std::map<std::pair<int, int>, int>& probMap);

    std::vector<Item*> GenerateDrops() const;

    nlohmann::json Serialize() const;
    static DropTable FromJson(const nlohmann::json& data);
};
