#include "actor.hpp"
#include "world.hpp"
#include "cell_content.hpp"
#include <iostream>

namespace rl {

    Actor::Actor(std::string name, Position startPos, World* worldContext, std::string symbol)
        : m_actorName(name), m_position(startPos), m_worldContext(worldContext), m_symbol(symbol) {
        if (m_worldContext != nullptr) {
            m_worldContext->registerActor(this);
        }
    }

    Actor::~Actor() {
        if (m_worldContext != nullptr) {
            m_worldContext->unregisterActor(this);
        }
        std::cout << "[Actor] Destructor: " << m_actorName << " destroyed.\n";
    }

    bool Actor::onCollisionEvent() {
        return true;
    }

    bool Actor::setActorLocation(Position newPos) {
        if (m_worldContext == nullptr) {
            return false;
        }

        bool pathIsClear = m_worldContext->canMoveTo(this, newPos);

        if (!pathIsClear) {
            return false;
        }

        m_position = newPos;
        m_worldContext->notifyCameraRefresh();

        return true;
    }

    Position Actor::getActorLocation() const { return m_position; }
    std::string Actor::getActorName() const { return m_actorName; }
    World* Actor::getWorldContext() const { return m_worldContext; }
    std::string Actor::getSymbol() const { return m_symbol; }

}
