#pragma once

namespace rl {
    struct Position {
        int x;
        int y;
        Position() : x(0), y(0) {}
        Position(int startX, int startY) : x(startX), y(startY) {}
    };
}