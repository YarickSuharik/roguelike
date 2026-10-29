#pragma once
#include "character.hpp"
#include <string>

namespace rl {

    class PlayerCharacter : public Character {
    public:
        PlayerCharacter(std::string name, Position startPos, World* worldContext, std::string symbol);
        virtual ~PlayerCharacter();
    };

}
