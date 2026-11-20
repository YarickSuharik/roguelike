#pragma once

namespace rl {

    class Character;

    class Controller {
    protected:
        Character* m_possessedCharacter;

    public:
        Controller();
        virtual ~Controller();

        virtual void possess(Character* character);
        virtual void update() = 0;

        Character* getPossessedCharacter() const;
    };

}
