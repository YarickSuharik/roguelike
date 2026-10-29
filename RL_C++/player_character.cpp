#include "player_character.hpp"
#include "controller.hpp"
#include "player_controller.hpp"

namespace rl {

    PlayerCharacter::PlayerCharacter(std::string name, Position startPos, World* worldContext, std::string symbol)
        : Character(name, startPos, worldContext, symbol)
    {
        setController(new PlayerController());
    }

    PlayerCharacter::~PlayerCharacter() {}

}
