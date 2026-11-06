#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <memory>
#include "world.hpp"
#include "actor.hpp"
#include "player_character.hpp"
#include "player_controller.hpp"
#include "camera.hpp"
#include "position.hpp"

namespace {

    void demoUniquePtr() {
        std::cout << "\n=== unique_ptr ===\n";

        {
            auto controller = std::make_unique<rl::PlayerController>();
            auto movedController = std::move(controller);

            std::cout << "[unique] ownership moved, source pointer empty: " << (controller == nullptr) << "\n";
        }

        std::cout << "[unique] block left, object destroyed without delete\n";

        {
            auto controllers = std::make_unique<rl::PlayerController[]>(3);
            std::cout << "[unique] array of three created without new[]\n";
        }

        std::cout << "[unique] array destroyed without delete[]\n";
    }

    void demoSharedPtr(const std::shared_ptr<rl::World>& world) {
        std::cout << "\n=== shared_ptr ===\n";

        std::weak_ptr<rl::Actor> ghost = world->spawnActor<rl::Actor>("SharedGhost", rl::Position(2, 2), "G");
        std::cout << "[shared] owners after spawn: " << ghost.use_count() << "\n";

        {
            auto keeper = ghost.lock();
            std::cout << "[shared] owners after lock(): " << keeper.use_count() << "\n";

            auto copy = keeper;
            std::cout << "[shared] owners after copy: " << copy.use_count() << "\n";
        }

        std::cout << "[shared] owners after copies destroyed: " << ghost.use_count() << "\n";

        {
            auto locked = ghost.lock();
            world->destroyActor(locked.get());
        }

        std::cout << "[shared] world released the last owner, expired: " << ghost.expired() << "\n";
    }

    void demoWeakPtr(const std::shared_ptr<rl::World>& world) {
        std::cout << "\n=== weak_ptr ===\n";

        std::weak_ptr<rl::Actor> ghost = world->spawnActor<rl::Actor>("WeakGhost", rl::Position(3, 2), "W");

        if (auto alive = ghost.lock()) {
            std::cout << "[weak] lock() works while object is alive: " << alive->getActorName() << "\n";
            world->destroyActor(alive.get());
        }

        std::cout << "[weak] lock() returns empty after death: " << (ghost.lock() == nullptr) << "\n";
        std::cout << "[weak] expired(): " << ghost.expired() << "\n";
    }

}

int main() {
    SetConsoleOutputCP(65001);
    std::cout << std::boolalpha;

    auto gameWorld = std::make_shared<rl::World>();

    if (!gameWorld->initializeMap("start_room.txt")) {
        std::cout << "Failed to load map data.\n";
        std::cin.get();
        return 1;
    }

    demoUniquePtr();
    demoSharedPtr(gameWorld);
    demoWeakPtr(gameWorld);

    std::cout << "\nPress any key to start the game.\n";
    _getch();

    std::weak_ptr<rl::PlayerCharacter> player =
        gameWorld->spawnActor<rl::PlayerCharacter>("Hero", rl::Position(5, 4), "@");
    gameWorld->setPlayerCharacter(player);

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
    }

    return 0;
}
