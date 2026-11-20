#pragma once
#include <memory>

namespace rl {

    class Character;

    class BaseController {
    private:
        int m_availableSteps;

    protected:
        std::weak_ptr<Character> m_possessedCharacter;

    public:
        BaseController();
        virtual ~BaseController();

        virtual void possess(const std::weak_ptr<Character>& character);

        void update();
        virtual void makeStep() = 0;

        void setAvailableSteps(int steps);
        int getAvailableSteps() const;

        std::weak_ptr<Character> getPossessedCharacter() const;
    };

}