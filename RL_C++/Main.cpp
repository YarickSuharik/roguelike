#include <Windows.h>
#include <memory>
#include <iostream>
#include "world.hpp"
#include "actor.hpp"
#include "character.hpp"
#include "player_character.hpp"
#include "base_controller.hpp"
#include "ai_controller.hpp"
#include "camera.hpp"
#include "position.hpp"

int main() {
    SetConsoleOutputCP(65001);

    auto gameWorld = std::make_shared<rl::World>();

    if (!gameWorld->initializeMap("start_room.txt")) {
        std::cout << "Failed to load map data.\n";
        std::cin.get();
        return 1;
    }

    std::weak_ptr<rl::PlayerCharacter> player =
        gameWorld->spawnActor<rl::PlayerCharacter>("Hero", rl::Position(5, 4), "@");
    gameWorld->setPlayerCharacter(player);

    gameWorld->spawnActor<rl::Actor>("Chest", rl::Position(15, 2), "C");

    std::weak_ptr<rl::Character> slime =
        gameWorld->spawnActor<rl::Character>("Slime", rl::Position(18, 4), "E");

    if (auto slimeCharacter = slime.lock()) {
        slimeCharacter->setController(std::make_unique<rl::AIController>());
    }

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

        if (auto slimeCharacter = slime.lock()) {
            if (auto controller = slimeCharacter->getController()) {
                controller->update();
            }
        }
    }

    return 0;
}