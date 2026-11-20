#include "ai_controller.hpp"
#include "character.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <random>

namespace rl {

    namespace {
        const int DIRECTION_COUNT = 8;
        const int DIRECTION_DX[DIRECTION_COUNT] = { -1, 0, 1, -1, 1, -1, 0, 1 };
        const int DIRECTION_DY[DIRECTION_COUNT] = { -1, -1, -1, 0, 0, 1, 1, 1 };

        std::mt19937& randomGenerator() {
            static std::mt19937 generator(std::random_device{}());
            return generator;
        }
    }

    AIController::AIController() : BaseController() {
        std::cout << "[AIController] Constructor\n";
    }

    AIController::~AIController() {
        std::cout << "[AIController] Destructor\n";
    }

    void AIController::makeStep() {
        auto character = m_possessedCharacter.lock();

        if (!character) return;

        std::array<int, DIRECTION_COUNT> directions;
        for (int i = 0; i < DIRECTION_COUNT; ++i) {
            directions[i] = i;
        }

        std::shuffle(directions.begin(), directions.end(), randomGenerator());

        for (int direction : directions) {
            if (character->moveRelative(DIRECTION_DX[direction], DIRECTION_DY[direction])) {
                return;
            }
        }
    }

    std::unique_ptr<BaseController> AIController::clone() const {
        return std::make_unique<AIController>();
    }

}