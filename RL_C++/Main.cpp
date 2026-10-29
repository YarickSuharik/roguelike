#include <Windows.h>
#include "world.hpp"
#include "actor.hpp"
#include "player_character.hpp"
#include "controller.hpp"
#include "camera.hpp"
#include "position.hpp"
#include <iostream>

int main() {
    SetConsoleOutputCP(65001);

    rl::World gameWorld;

    if (!gameWorld.initializeMap("start_room.txt")) {
        std::cout << "Failed to load map data.\n";
        std::cin.get();
        return 1;
    }

    // Создаем персонажа игрока и статический объект окружения
    rl::PlayerCharacter* player = new rl::PlayerCharacter("Hero", rl::Position(5, 4), &gameWorld, "@");
    rl::Actor* chest = new rl::Actor("Chest", rl::Position(15, 2), &gameWorld, "C");

    gameWorld.setPlayerCharacter(player);

    rl::Camera gameCamera(rl::Position(0, 0), 41, 31, &gameWorld);
    gameCamera.setTrackedActor(player);
    gameWorld.registerCamera(&gameCamera);
    gameCamera.refresh();

    while (true) {
        rl::Controller* playerController = player->getController();
        if (playerController != nullptr) {
            playerController->update();
        }
    }

    delete chest;
    delete player;

    return 0;
}
