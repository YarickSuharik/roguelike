#include "player_controller.hpp"
#include "character.hpp"
#include "position.hpp"
#include <conio.h>
#include <iostream>

namespace rl {

    PlayerController::PlayerController() : BaseController() {
        std::cout << "[PlayerController] Constructor\n";
    }

    PlayerController::~PlayerController() {
        std::cout << "[PlayerController] Destructor\n";
    }

    void PlayerController::makeStep() {
        auto character = m_possessedCharacter.lock();

        if (!character) return;

        while (true) {
            int key = _getch();

            int dx = 0;
            int dy = 0;
            bool wantsToMove = false;

            switch (key) {
            case 'q': case 'Q': dx = -1; dy = -1; wantsToMove = true; break;
            case 'w': case 'W': dx = 0; dy = -1; wantsToMove = true; break;
            case 'e': case 'E': dx = 1; dy = -1; wantsToMove = true; break;
            case 'a': case 'A': dx = -1; dy = 0; wantsToMove = true; break;
            case 'd': case 'D': dx = 1; dy = 0; wantsToMove = true; break;
            case 'z': case 'Z': dx = -1; dy = 1; wantsToMove = true; break;
            case 'x': case 'X': dx = 0; dy = 1; wantsToMove = true; break;
            case 'c': case 'C': dx = 1; dy = 1; wantsToMove = true; break;
            default: break;
            }

            if (wantsToMove && character->moveRelative(dx, dy)) {
                return;
            }
        }
    }

    std::unique_ptr<BaseController> PlayerController::clone() const {
        return std::make_unique<PlayerController>();
    }

}