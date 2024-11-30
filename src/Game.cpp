#include "Game.h"

#include <time.h>
#include <map>

#include <Config.h>
#include <GlobalFunctions.h>
#include <ResourceWorldObject.h>
#include <Player.h>
#include <GameTypes.h>

Game* Game::instance = nullptr;


// TODO: Add main menu
// TODO: Add pause menu
// TODO: Add building system
// TODO: Add category to entities and items
// TODO: Add intialization of characteristcs to entities
// TODO: Merge ResourceWorldObject and WorldObject
// TODO: Make so adding items to inventory will stack count correctly
// TODO: Optimize world tiles saving and loading to save only type and position of tiles


void GenerateWorld(World* world, int worldHeight, int worldWidth)
{
    const float ISLAND_RADIUS_FACTOR = 0.4f;
    const float COAST_VARIANCE = 0.1f;

    std::srand(std::time(nullptr));

    // Center of the world, treating it as the center of the island
    int centerX = 0;
    int centerY = 0;
    float maxDistance = (
        std::sqrt(std::pow(worldWidth / 2, 2) + 
        std::pow(worldHeight / 2, 2)) * 
        ISLAND_RADIUS_FACTOR
    );

    std::map<std::vector<std::string>, int> landObjectsGeneratorSettings = {
        { { WorldObjectType::ROCK }, 1 },
        { { WorldObjectType::TREE, WorldObjectType::TREE_BIG }, 1 },
        { { WorldObjectType::BUSH }, 1 },
        { { WorldObjectType::SUNFLOWER }, 1 },
        { { WorldObjectType::WHEAT }, 1 },
        { { WorldObjectType::TOMATO }, 1 }
    };

    std::map<std::vector<std::string>, int> waterObjectsGeneratorSettings = {
        { { WorldObjectType::LILYPAD }, 1 }
    };

    for (int x = -worldWidth / 2; x < worldWidth / 2; x++)
    {
        for (int y = -worldHeight / 2; y < worldHeight / 2; y++)
        {
            // Calculate distance from the center
            float distanceToCenter = std::sqrt(std::pow(x - centerX, 2) + std::pow(y - centerY, 2));

            // Add some randomness to the coastline
            float coastlineDistance = maxDistance + (std::rand() % 100 / 100.0f - 0.5f) * COAST_VARIANCE * maxDistance;

            // Set tile type based on distance with randomness for uneven coastlines
            if (distanceToCenter < coastlineDistance)
            {
                world->SetTile(TileType::GRASS, Point(x, y)); // Inside island boundary

                // Place objects
                for (auto& objectGenerator : landObjectsGeneratorSettings)
                {
                    if (std::rand() % 100 < objectGenerator.second)
                    {
                        std::string objectType = objectGenerator.first[std::rand() % objectGenerator.first.size()];

                        world->AddObject(objectType, Point(x * 100, y * 100));

                        break;
                    }
                }
            }
            else
            {
                world->SetTile(TileType::WATER, Point(x, y)); // Outside island boundary

                // Place lilypads if close to the coast
                if (distanceToCenter < coastlineDistance + 5)
                {
                    for (auto& objectGenerator : waterObjectsGeneratorSettings)
                    {
                        if (std::rand() % 100 < objectGenerator.second)
                        {
                            std::string objectType = objectGenerator.first[std::rand() % objectGenerator.first.size()];

                            world->AddObject(objectType, Point(x * 100, y * 100));

                            break;
                        }
                    }
                }
            }
        }
    }
}


Game::Game()
{
    instance = this;

    Size screenSize = GetScreenSize();

    if (Config::USE_CONFIG_WINDOW_SIZE)
        this->windowSize = Config::WINDOW_SIZE;

    else
        this->windowSize = screenSize;

    this->windowTitle = Config::WINDOW_TITLE;

    this->window = SDL_CreateWindow(
        windowTitle.c_str(), 
        this->windowSize.width, 
        this->windowSize.height, 
        NULL
    );

    if (Config::BORDERLESS)
    {
        SDL_SetWindowBordered(this->window, false);
        SDL_SetWindowPosition(this->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    }
    else
    {
        // Get window title bar height
        int topBorderSize;
        SDL_GetWindowBordersSize(this->window, &topBorderSize, NULL, NULL, NULL);

        // Subtract title bar height from window height
        this->windowSize.height -= topBorderSize;

        SDL_SetWindowSize(this->window, this->windowSize.width, this->windowSize.height);
        SDL_SetWindowPosition(this->window, SDL_WINDOWPOS_CENTERED, topBorderSize);
    }

    this->SDLRenderer = SDL_CreateRenderer(
        this->window, NULL
    );

    std::string basePath = SDL_GetBasePath();

    this->renderer = new Renderer(
        this->SDLRenderer, windowSize, 
        basePath + "resources/textures/", 
        1.1f
    );

    this->LoadAssets();

    // Create world
    this->world = new World();

    clock_t begin = clock();

    GenerateWorld(this->world, 100, 100);

    SDL_Log("World generation took %f seconds", float(clock() - begin) / CLOCKS_PER_SEC);

    // Add player
    this->world->AddEntity(
        Factory::CreateEntity(EntityType::PLAYER, Point(0, 0), "Player")
    );

    this->world->Save(basePath + "worlds/world.json");

    this->gui = new GameGUI();

    this->ready = true;
}

Game::~Game()
{
    this->ready = false;

    SDL_DestroyRenderer(this->SDLRenderer);
    SDL_DestroyWindow(this->window);

    delete this->renderer;
}


void Game::LoadAssets()
{
    // Tile textures
    this->renderer->LoadTexture("grass", "grass.png", Point(0, 0));
    this->renderer->LoadTexture("water", "water.png");

    // Object textures
    this->renderer->LoadTexture("rock", "rock.png");
    this->renderer->LoadTexture("tree", "tree.png", Point(0, 100));
    this->renderer->LoadTexture("tree_big", "tree_big.png", Point(50, 150));
    this->renderer->LoadTexture("bush", "bush.png");
    this->renderer->LoadTexture("sunflower", "sunflower.png", Point(-12.5, 75));
    this->renderer->LoadTexture("lilypad", "lilypad.png", Point(-12.5, -12.5));
    this->renderer->LoadTexture("wheat", "wheat.png", Point(-12.5, -12.5));
    this->renderer->LoadTexture("tomato", "tomato.png", Point(-12.5, -12.5));

    // Entity textures
    this->renderer->LoadTexture("player", "player.png");
    this->renderer->LoadTexture("golem", "golem.png");

    // Item textures
    this->renderer->LoadTexture("axe_item", "axe_item.png");
    this->renderer->LoadTexture("rock_item", "rock_item.png");
    this->renderer->LoadTexture("wood_item", "wood_item.png");
    this->renderer->LoadTexture("wheat_item", "wheat_item.png");
    this->renderer->LoadTexture("tomato_item", "tomato_item.png");

    // GUI textures
    this->renderer->LoadTexture("selection", "selection.png");
    this->renderer->LoadTexture("inventory_slot", "inventory_slot.png");

    // Font textures
    this->renderer->LoadFont("font", "font.png");
}


Game* Game::GetInstance()
{
    return instance;
}

bool Game::IsReady()
{
    return this->ready;
}


Renderer* Game::GetRenderer()
{
    return this->renderer;
}


void Game::Update(float deltaTime)
{
    this->world->Update(deltaTime);

    // Get objects at mouse position
    if (IsMousePressed(LEFT))
    {
        Point mousePosition = this->renderer->ScreenToWorld(GetMousePosition());

        std::vector<WorldObject*> objectsAtMouse = this->world->GetObjectsAt(mousePosition);

        if (objectsAtMouse.size() > 0)
        {
            WorldObject* object = objectsAtMouse[0];

            // Check if object is a resource object
            if (object != nullptr && object->GetCategory() == WorldObjectCategory::RESOURCE_OBJECT)
            {
                ResourceWorldObject* resourceObject = dynamic_cast<ResourceWorldObject*>(object);

                // Damage resource object
                if (!resourceObject->IsDestroyed())
                {
                    resourceObject->Damage(this->world->GetPlayer()->GetAttack());

                    // Drop items if destroyed
                    if (resourceObject->IsDestroyed())
                    {
                        Inventory* inventory = this->world->GetPlayer()->GetInventory();

                        for (auto& item : resourceObject->GetDropTable().GenerateDrops())
                            inventory->AddItem(item);
                    }
                }
            }
        }
    }
}

void Game::Render(float deltaTime)
{
    this->renderer->PreRender();

    // Update renderer viewport
    this->renderer->CenterViewPortAtPosition(
        this->world->GetPlayer()->GetCenter()
    );

    this->world->Render(this->renderer, deltaTime);

    // Render GUI
    this->gui->Render(this->renderer, deltaTime, this->world->GetPlayer());

    this->renderer->PostRender();
}
