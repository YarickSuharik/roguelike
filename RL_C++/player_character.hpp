#pragma once
#include "character.hpp"
#include <string>

namespace rl {

    class PlayerCharacter : public Character {
    public:
        PlayerCharacter(std::string name, Position startPos, const std::weak_ptr<World>& worldContext, std::string symbol);
        virtual ~PlayerCharacter();

        virtual void onSpawned() override;
    };

}
