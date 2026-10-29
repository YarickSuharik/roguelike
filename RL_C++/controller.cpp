#include "controller.hpp"
#include "character.hpp"

namespace rl {

    Controller::Controller() : m_possessedCharacter(nullptr) {}

    Controller::~Controller() {}

    void Controller::possess(Character* character) {
        m_possessedCharacter = character;
    }

    Character* Controller::getPossessedCharacter() const {
        return m_possessedCharacter;
    }

}
