#pragma once
#include "position.hpp"
#include <string>

namespace rl {

    class World;

    class Actor {
    private:
        Position m_position;
        std::string m_actorName;
        std::string m_symbol;
    protected:
        World* m_worldContext;
    public:
        Actor(std::string name, Position startPos, World* worldContext, std::string symbol);
        virtual ~Actor();

        virtual bool onCollisionEvent();

        bool setActorLocation(Position newPos);

        Position getActorLocation() const;
        std::string getActorName() const;
        World* getWorldContext() const;
        std::string getSymbol() const;
    };

}
