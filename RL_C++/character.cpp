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

    // копия получает клон контроллера того же типа, но без пешки: possess() требует shared_from_this()
    Character::Character(const Character& other)
        : Actor(other),
          m_controller(other.m_controller ? other.m_controller->clone() : nullptr),
          m_availableSteps(other.m_availableSteps) {
        std::cout << "[Character] Copy constructor: " << getActorName() << "\n";
    }

    Character::Character(Character&& other) noexcept
        : Actor(std::move(other)),
          m_controller(std::move(other.m_controller)),
          m_availableSteps(other.m_availableSteps) {
        other.m_availableSteps = 0;
        std::cout << "[Character] Move constructor: " << getActorName() << "\n";
    }

    Character& Character::operator=(const Character& other) {
        if (this != &other) {
            Actor::operator=(other);
            m_controller = other.m_controller ? other.m_controller->clone() : nullptr;
            m_availableSteps = other.m_availableSteps;
        }

        std::cout << "[Character] Copy assignment: " << getActorName() << "\n";
        return *this;
    }

    Character& Character::operator=(Character&& other) noexcept {
        if (this != &other) {
            Actor::operator=(std::move(other));
            m_controller = std::move(other.m_controller);
            m_availableSteps = other.m_availableSteps;
            other.m_availableSteps = 0;
        }

        std::cout << "[Character] Move assignment: " << getActorName() << "\n";
        return *this;
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

    std::unique_ptr<Character> Character::clone() const {
        return std::make_unique<Character>(*this);
    }

}