#include "controller.hpp"
#include "character.hpp"
#include <iostream>

namespace rl {

    Controller::Controller() {}

    Controller::~Controller() { std::cout << "[Controller] Destructor: Controller destroyed.\n"; }

    void Controller::possess(const std::weak_ptr<Character>& character) {
        m_possessedCharacter = character;
    }

    std::weak_ptr<Character> Controller::getPossessedCharacter() const {
        return m_possessedCharacter;
    }

}
