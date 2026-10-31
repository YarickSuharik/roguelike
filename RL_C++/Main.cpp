#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "world.hpp"
#include "actor.hpp"
#include "player_character.hpp"
#include "controller.hpp"
#include "player_controller.hpp"
#include "camera.hpp"
#include "position.hpp"

// тестовые функиции дл€ работы со ссылувми и указател€ми

void demoByReference(rl::Actor& actor) {
    std::cout << "[ref] " << actor.getActorName() << " at ("
        << actor.getActorLocation().x << "," << actor.getActorLocation().y << ")\n";
    actor.setActorLocation(rl::Position(actor.getActorLocation().x + 1, actor.getActorLocation().y));
}

void demoByPointer(rl::Actor* actor) {
    if (actor == nullptr) return;
    std::cout << "[ptr] " << actor->getActorName() << " at ("
        << actor->getActorLocation().x << "," << actor->getActorLocation().y << ")\n";
    actor->setActorLocation(rl::Position(actor->getActorLocation().x - 1, actor->getActorLocation().y));
}

// конец

int main() {
    SetConsoleOutputCP(65001);

    rl::World gameWorld;

    if (!gameWorld.initializeMap("start_room.txt")) {
        std::cout << "Failed to load map data.\n";
        std::cin.get();
        return 1;
    }

    // —оздаем персонажа игрока и статический объект окружени€
    rl::PlayerCharacter* player = new rl::PlayerCharacter("Hero", rl::Position(5, 4), &gameWorld, "@");
    rl::Actor* chest = new rl::Actor("Chest", rl::Position(15, 2), &gameWorld, "C");

    // тестовый персонаж и тд
    rl::Character* secondPlayer = new rl::Character("SecondHero", rl::Position(4, 4), &gameWorld, "S");
    secondPlayer->setController(new rl::PlayerController());
    rl::Actor* refActor;
    rl::Controller* controllerArray;
    rl::Actor** actorArray;

    gameWorld.setPlayerCharacter(player);

    rl::Camera gameCamera(rl::Position(0, 0), 41, 31, &gameWorld);
    gameCamera.setTrackedActor(player);
    gameWorld.registerCamera(&gameCamera);
    gameCamera.refresh();

    int stepCount = 0;

    while (true) {
        rl::Controller* playerController = player->getController();
        if (playerController != nullptr) {
            playerController->update();

            stepCount++;

            switch (stepCount) {
            case 1: // удаление части (агрегаци€)
                secondPlayer->setController(nullptr);
                break;
            case 2: // возвращение
                secondPlayer->setController(new rl::PlayerController());
                break;
            case 3: // удаление целого (композици€)
                delete secondPlayer;
                secondPlayer = nullptr;
                break;
            case 4: // статик
            {
                static rl::Actor staticActor("StaticGhost", rl::Position(20, 4), &gameWorld, "S");
                gameCamera.refresh();
            }
                break;
            case 5: // ссылки и указатели
                refActor = new rl::Actor("RefGhost", rl::Position(15, 4), &gameWorld, "R");
                demoByReference(*refActor);   // по ссылке Ч сдвиг вправо (31,4)
                gameCamera.refresh(); 
                _getch();
                demoByPointer(refActor);      // по указателю Ч сдвиг влево (30,4)
                gameCamera.refresh(); 
                _getch();
                delete refActor;
                break;
            case 6: // динамический массив
                controllerArray = new rl::PlayerController[3];
                delete[] controllerArray;
                controllerArray = nullptr;
                break;
            case 7: // динамические объекты
                actorArray = new rl::Actor* [3];
                actorArray[0] = new rl::Actor("GhostA", rl::Position(13, 4), &gameWorld, "A");
                actorArray[1] = new rl::Actor("GhostB", rl::Position(14, 4), &gameWorld, "B");
                actorArray[2] = new rl::Actor("GhostC", rl::Position(16, 4), &gameWorld, "D");
                gameCamera.refresh(); 
                _getch();
                for (int i = 0; i < 3; ++i) { delete actorArray[i]; }
                delete[] actorArray;
                break;
            }
        }
    }

    delete chest;
    delete secondPlayer;
    if (player != nullptr) {
        delete player;
    }

    return 0;
}
