#include <Windows.h>
#include "world.hpp"
#include "actor.hpp"
#include "camera.hpp"
#include "position.hpp"
#include <iostream>
#include <conio.h>

int main() {
    SetConsoleOutputCP(65001);

    rl::World gameWorld;

    if (!gameWorld.initializeMap("start_room.txt")) {
        std::cout << "Failed to load map data.\n";
        std::cin.get();
        return 1;
    }

    rl::Actor* player = new rl::Actor("Hero", rl::Position(5, 4), &gameWorld, "@");
    rl::Actor* chest = new rl::Actor("Chest", rl::Position(15, 2), &gameWorld, "C");

    rl::Camera gameCamera(rl::Position(0, 0), 41, 31, &gameWorld);
    gameCamera.setTrackedActor(player);

    gameWorld.registerCamera(&gameCamera);

    gameCamera.refreshCamera();
    _getch();

    chest->setActorLocation(rl::Position(-5, -5));

    chest->setActorLocation(rl::Position(0, 1));

    chest->setActorLocation(rl::Position(10, 2));

    player->setActorLocation(rl::Position(15, 4));

    _getch();

    delete chest;
    delete player;

    return 0;
}
