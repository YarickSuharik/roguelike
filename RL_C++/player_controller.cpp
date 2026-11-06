#include "player_controller.hpp"
#include "character.hpp"
#include "position.hpp"
#include <conio.h>

namespace rl {

    PlayerController::PlayerController() : Controller() {}

    PlayerController::~PlayerController() {}

    void PlayerController::update() {
        if (m_possessedCharacter == nullptr) return;

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

        if (wantsToMove) {
            m_possessedCharacter->moveRelative(dx, dy);
        }
    }

}
