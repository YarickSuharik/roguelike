#pragma once
#include "actor.hpp"
#include "position.hpp"
#include <memory>
#include <string>

namespace rl {

    class BaseController;

    // контроллер хранит слабую ссылку на персонажа, поэтому персонаж умеет отдать weak_ptr на себя
    class Character : public Actor, public std::enable_shared_from_this<Character> {
    private:
        std::unique_ptr<BaseController> m_controller;
        int m_availableSteps;

    public:
        Character(std::string name, Position startPos, const std::weak_ptr<World>& worldContext, std::string symbol);
        Character(const Character& other);
        Character(Character&& other) noexcept;
        Character& operator=(const Character& other);
        Character& operator=(Character&& other) noexcept;
        virtual ~Character();

        void setController(std::unique_ptr<BaseController> controller);
        BaseController* getController() const;

        void setAvailableSteps(int steps);
        int getAvailableSteps() const;

        bool moveRelative(int dx, int dy);

        virtual std::unique_ptr<Character> clone() const;
    };

}