#pragma once
#include "actor.hpp"
#include "position.hpp"
#include <string>

namespace rl {

    class Controller;

    class Character : public Actor {
    private:
        Controller* m_controller;

    public:
        Character(std::string name, Position startPos, World* worldContext, std::string symbol);
        virtual ~Character();

        void setController(Controller* controller);
        Controller* getController() const;

        bool moveRelative(int dx, int dy);
    };

}
