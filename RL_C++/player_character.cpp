#include "player_character.hpp"
#include "player_controller.hpp"
#include <memory>
#include <utility>

namespace rl {

    PlayerCharacter::PlayerCharacter(std::string name, Position startPos, const std::weak_ptr<World>& worldContext, std::string symbol)
        : Character(std::move(name), startPos, worldContext, std::move(symbol)) {}

    PlayerCharacter::~PlayerCharacter() {}

    void PlayerCharacter::onSpawned() {
        setController(std::make_unique<PlayerController>());
    }

}
