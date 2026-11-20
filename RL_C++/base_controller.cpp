#include "base_controller.hpp"
#include "character.hpp"
#include <iostream>

namespace rl {

    BaseController::BaseController() : m_availableSteps(1) {}

    BaseController::~BaseController() { std::cout << "[BaseController] Destructor\n"; }

    void BaseController::possess(const std::weak_ptr<Character>& character) {
        m_possessedCharacter = character;
    }

    void BaseController::update() {
        for (int i = 0; i < m_availableSteps; ++i) {
            makeStep();
        }
    }

    void BaseController::setAvailableSteps(int steps) {
        m_availableSteps = steps > 0 ? steps : 0;
    }

    int BaseController::getAvailableSteps() const {
        return m_availableSteps;
    }

    std::weak_ptr<Character> BaseController::getPossessedCharacter() const {
        return m_possessedCharacter;
    }

}