#pragma once
#include "position.hpp"
#include <memory>
#include <string>

namespace rl {

    class World;

    class Actor {
    private:
        Position m_position;
        std::string m_actorName;
        std::string m_symbol;
    protected:
        std::weak_ptr<World> m_worldContext;
    public:
        Actor(std::string name, Position startPos, const std::weak_ptr<World>& worldContext, std::string symbol);
        virtual ~Actor();

        virtual void onSpawned();
        virtual bool onCollisionEvent();

        bool setActorLocation(Position newPos);

        Position getActorLocation() const;
        std::string getActorName() const;
        std::weak_ptr<World> getWorldContext() const;
        std::string getSymbol() const;
    };

}
