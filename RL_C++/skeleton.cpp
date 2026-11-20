#include "skeleton.hpp"
#include "ai_controller.hpp"
#include <iostream>
#include <memory>
#include <utility>

namespace rl {

    Skeleton::Skeleton()
        : Character("Skeleton", Position(0, 0), std::weak_ptr<World>(), "S") {
        std::cout << "[Skeleton] Default constructor\n";
    }

    Skeleton::Skeleton(std::string name, Position startPos, const std::weak_ptr<World>& worldContext, std::string symbol)
        : Character(std::move(name), startPos, worldContext, std::move(symbol)) {
        std::cout << "[Skeleton] Constructor: " << getActorName() << "\n";
    }

    Skeleton::~Skeleton() {
        std::cout << "[Skeleton] Destructor: " << getActorName() << "\n";
    }

    void Skeleton::onSpawned() {
        setController(std::make_unique<AIController>());
    }

}