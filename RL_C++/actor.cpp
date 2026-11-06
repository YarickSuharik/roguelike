#include "actor.hpp"
#include "world.hpp"
#include <iostream>
#include <utility>

namespace rl {

    Actor::Actor(std::string name, Position startPos, const std::weak_ptr<World>& worldContext, std::string symbol)
        : m_position(startPos), m_actorName(std::move(name)), m_symbol(std::move(symbol)), m_worldContext(worldContext) {}

    Actor::~Actor() {
        std::cout << "[Actor] Destructor: " << m_actorName << " destroyed.\n";
    }

    void Actor::onSpawned() {}

    bool Actor::onCollisionEvent() {
        return true;
    }

    bool Actor::setActorLocation(Position newPos) {
        auto world = m_worldContext.lock();

        if (!world) {
            return false;
        }

        if (!world->canMoveTo(this, newPos)) {
            return false;
        }

        m_position = newPos;
        world->notifyCameraRefresh();

        return true;
    }

    Position Actor::getActorLocation() const { return m_position; }
    std::string Actor::getActorName() const { return m_actorName; }
    std::weak_ptr<World> Actor::getWorldContext() const { return m_worldContext; }
    std::string Actor::getSymbol() const { return m_symbol; }

}
