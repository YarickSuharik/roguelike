#include "character.hpp"
#include "base_controller.hpp"
#include "world.hpp"
#include <iostream>
#include <utility>

namespace rl {

    Character::Character(std::string name, Position startPos, const std::weak_ptr<World>& worldContext, std::string symbol)
        : Actor(std::move(name), startPos, worldContext, std::move(symbol)), m_availableSteps(1) {
        std::cout << "[Character] Constructor: " << getActorName() << "\n";
    }

    Character::~Character() {
        std::cout << "[Character] Destructor: " << getActorName() << "\n";
    }

    // вызывать после того, как объект создан через spawnActor: shared_from_this() требует живого владельца
    void Character::setController(std::unique_ptr<BaseController> controller) {
        m_controller = std::move(controller);

        if (m_controller) {
            m_controller->possess(shared_from_this());
        }
    }

    BaseController* Character::getController() const {
        return m_controller.get();
    }

    void Character::setAvailableSteps(int steps) {
        m_availableSteps = steps > 0 ? steps : 0;
    }

    int Character::getAvailableSteps() const {
        return m_availableSteps;
    }

    bool Character::moveRelative(int dx, int dy) {
        if (m_worldContext.expired()) {
            return false;
        }

        Position currentPos = getActorLocation();
        Position targetPos(currentPos.x + dx, currentPos.y + dy);

        return setActorLocation(targetPos);
    }

}