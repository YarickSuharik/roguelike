#pragma once
#include "character.hpp"
#include <string>

namespace rl {

    class Skeleton : public Character {
    public:
        Skeleton();
        Skeleton(std::string name, Position startPos, const std::weak_ptr<World>& worldContext, std::string symbol);
        virtual ~Skeleton();

        virtual void onSpawned() override;
    };

}