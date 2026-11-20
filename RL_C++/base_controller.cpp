#include "base_controller.hpp"
#include "character.hpp"
#include <iostream>

namespace rl {

    BaseController::BaseController() {
        std::cout << "[BaseController] Constructor\n";
    }

    BaseController::~BaseController() {
        std::cout << "[BaseController] Destructor\n";
    }

    void BaseController::possess(const std::weak_ptr<Character>& character) {
        m_possessedCharacter = character;
    }

    void BaseController::update() {
        auto character = m_possessedCharacter.lock();

        if (!character) return;

        int steps = character->getAvailableSteps();

        for (int i = 0; i < steps; ++i) {
            makeStep();
        }
    }

    std::string BaseController::describe() const {
        auto character = m_possessedCharacter.lock();

        if (!character) {
            return "BaseController idle";
        }

        return "BaseController on " + character->getActorName();
    }

    std::weak_ptr<Character> BaseController::getPossessedCharacter() const {
        return m_possessedCharacter;
    }

}