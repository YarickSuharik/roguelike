#include "character.hpp"
#include "controller.hpp"
#include "world.hpp"

namespace rl {

    Character::Character(std::string name, Position startPos, World* worldContext, std::string symbol)
        : Actor(name, startPos, worldContext, symbol), m_controller(nullptr) {}

    Character::~Character() {
        if (m_controller != nullptr) {
            delete m_controller;
        }
    }

    void Character::setController(Controller* controller) {
        if (m_controller != nullptr) {
            delete m_controller;
        }
        m_controller = controller;
        if (m_controller != nullptr) {
            m_controller->possess(this);
        }
    }

    Controller* Character::getController() const {
        return m_controller;
    }

    bool Character::moveRelative(int dx, int dy) {
        if (m_worldContext == nullptr) return false;

        Position currentPos = getActorLocation();
        Position targetPos(currentPos.x + dx, currentPos.y + dy);
        
        setActorLocation(targetPos);
        return true;
    }

}
