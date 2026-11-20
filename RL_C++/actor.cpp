#include "actor.hpp"
#include "world.hpp"
#include <iostream>
#include <utility>

namespace rl {

    Actor::Actor(std::string name, Position startPos, const std::weak_ptr<World>& worldContext, std::string symbol)
        : m_position(startPos), m_actorName(std::move(name)), m_symbol(std::move(symbol)), m_worldContext(worldContext) {
        std::cout << "[Actor] Constructor: " << m_actorName << "\n";
    }

    Actor::Actor(const Actor& other)
        : m_position(other.m_position), m_actorName(other.m_actorName), m_symbol(other.m_symbol), m_worldContext(other.m_worldContext) {
        std::cout << "[Actor] Copy constructor: " << m_actorName << "\n";
    }

    Actor::Actor(Actor&& other) noexcept
        : m_position(other.m_position), m_actorName(std::move(other.m_actorName)), m_symbol(std::move(other.m_symbol)), m_worldContext(other.m_worldContext) {
        std::cout << "[Actor] Move constructor: " << m_actorName << "\n";
    }

    Actor& Actor::operator=(const Actor& other) {
        if (this != &other) {
            m_position = other.m_position;
            m_actorName = other.m_actorName;
            m_symbol = other.m_symbol;
            m_worldContext = other.m_worldContext;
        }

        std::cout << "[Actor] Copy assignment: " << m_actorName << "\n";
        return *this;
    }

    Actor& Actor::operator=(Actor&& other) noexcept {
        if (this != &other) {
            m_position = other.m_position;
            m_actorName = std::move(other.m_actorName);
            m_symbol = std::move(other.m_symbol);
            m_worldContext = other.m_worldContext;
        }

        std::cout << "[Actor] Move assignment: " << m_actorName << "\n";
        return *this;
    }

    Actor::~Actor() {
        std::cout << "[Actor] Destructor: " << m_actorName << "\n";
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