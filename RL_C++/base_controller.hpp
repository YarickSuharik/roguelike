#pragma once
#include <memory>
#include <string>

namespace rl {

    class Character;

    class BaseController {
    protected:
        std::weak_ptr<Character> m_possessedCharacter;

    public:
        BaseController();
        virtual ~BaseController();

        virtual void possess(const std::weak_ptr<Character>& character);

        void update();
        virtual void makeStep() = 0;
        virtual std::unique_ptr<BaseController> clone() const = 0;
        virtual std::string describe() const;

        std::weak_ptr<Character> getPossessedCharacter() const;
    };

}