#pragma once
#include <memory>

namespace rl {

    class Character;

    class Controller {
    protected:
        std::weak_ptr<Character> m_possessedCharacter;

    public:
        Controller();
        virtual ~Controller();

        virtual void possess(const std::weak_ptr<Character>& character);
        virtual void update() = 0;

        std::weak_ptr<Character> getPossessedCharacter() const;
    };

}
