#pragma once

namespace rl {

    class Actor;

    struct CellContent {
        bool isWall;
        Actor* actorPtr;

        CellContent() : isWall(false), actorPtr(nullptr) {}
        CellContent(bool wall, Actor* actor) : isWall(wall), actorPtr(actor) {}
    };

}
