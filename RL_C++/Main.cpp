#include <Windows.h>
#include <conio.h>
#include <memory>
#include <iostream>
#include "world.hpp"
#include "actor.hpp"
#include "character.hpp"
#include "player_character.hpp"
#include "base_controller.hpp"
#include "ai_controller.hpp"
#include "skeleton.hpp"
#include "camera.hpp"
#include "position.hpp"

namespace {

    void demoConstructors() {
        std::cout << "\n=== constructor with parameters ===\n";
        {
            rl::Skeleton skeleton("DemoSkeleton", rl::Position(0, 0), std::weak_ptr<rl::World>(), "S");
        }

        std::cout << "\n=== default constructor ===\n";
        {
            rl::Skeleton defaultSkeleton;
        }

        std::cout << "\n=== destruction through base pointer ===\n";
        {
            std::unique_ptr<rl::BaseController> controller = std::make_unique<rl::AIController>();
            std::unique_ptr<rl::Character> basePointer = std::make_unique<rl::Skeleton>();
            std::cout << "--- leaving scope ---\n";
        }
    }

}

int main() {
    SetConsoleOutputCP(65001);

    auto gameWorld = std::make_shared<rl::World>();

    if (!gameWorld->initializeMap("start_room.txt")) {
        std::cout << "Failed to load map data.\n";
        std::cin.get();
        return 1;
    }

    demoConstructors();

    std::cout << "\nPress any key to start.\n";
    _getch();

    std::weak_ptr<rl::PlayerCharacter> player =
        gameWorld->spawnActor<rl::PlayerCharacter>("Hero", rl::Position(5, 4), "@");
    gameWorld->setPlayerCharacter(player);

    gameWorld->spawnActor<rl::Actor>("Chest", rl::Position(15, 2), "C");

    std::weak_ptr<rl::Skeleton> skeleton =
        gameWorld->spawnActor<rl::Skeleton>("Skeleton", rl::Position(18, 4), "S");

    auto gameCamera = std::make_shared<rl::Camera>(rl::Position(0, 0), 41, 31, gameWorld);
    gameCamera->setTrackedActor(player);
    gameWorld->registerCamera(gameCamera);
    gameCamera->refresh();

    while (true) {
        auto hero = player.lock();

        if (!hero) {
            break;
        }

        if (auto controller = hero->getController()) {
            controller->update();
        }

        if (auto skeletonCharacter = skeleton.lock()) {
            if (auto controller = skeletonCharacter->getController()) {
                controller->update();
            }
        }
    }

    return 0;
}