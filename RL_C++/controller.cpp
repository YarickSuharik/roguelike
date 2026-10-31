#include "controller.hpp"
#include "character.hpp"
#include <iostream>

namespace rl {

    Controller::Controller() : m_possessedCharacter(nullptr) {}

    Controller::~Controller() { std::cout << "[Controller] Destructor: " << "Controller" << " destroyed.\n"; }

    void Controller::possess(Character* character) {
        m_possessedCharacter = character;
    }

    Character* Controller::getPossessedCharacter() const {
        return m_possessedCharacter;
    }

}
