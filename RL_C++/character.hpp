#pragma once
#include "actor.hpp"
#include "position.hpp"
#include <memory>
#include <string>

namespace rl {

    class Controller;

    // контроллер хранит слабую ссылку на персонажа, поэтому персонаж умеет отдать weak_ptr на себя
    class Character : public Actor, public std::enable_shared_from_this<Character> {
    private:
        std::unique_ptr<Controller> m_controller;

    public:
        Character(std::string name, Position startPos, const std::weak_ptr<World>& worldContext, std::string symbol);
        virtual ~Character();

        void setController(std::unique_ptr<Controller> controller);
        Controller* getController() const;

        bool moveRelative(int dx, int dy);
    };

}
