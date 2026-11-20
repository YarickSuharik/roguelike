#pragma once
#include <memory>

namespace rl {

    class Actor;

    struct CellContent {
        bool isWall;
        std::weak_ptr<Actor> actorPtr;

        CellContent() : isWall(false) {}
        CellContent(bool wall, const std::weak_ptr<Actor>& actor) : isWall(wall), actorPtr(actor) {}
    };

}
