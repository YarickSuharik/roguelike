#include "character.hpp"
#include "controller.hpp"
#include "world.hpp"
#include <utility>

namespace rl {

    Character::Character(std::string name, Position startPos, const std::weak_ptr<World>& worldContext, std::string symbol)
        : Actor(std::move(name), startPos, worldContext, std::move(symbol)) {}

    Character::~Character() {}

    // вызывать после того, как объект создан через spawnActor: shared_from_this() требует живого владельца
    void Character::setController(std::unique_ptr<Controller> controller) {
        m_controller = std::move(controller);

        if (m_controller) {
            m_controller->possess(shared_from_this());
        }
    }

    Controller* Character::getController() const {
        return m_controller.get();
    }

    bool Character::moveRelative(int dx, int dy) {
        if (m_worldContext.expired()) {
            return false;
        }

        Position currentPos = getActorLocation();
        Position targetPos(currentPos.x + dx, currentPos.y + dy);

        setActorLocation(targetPos);
        return true;
    }

}
