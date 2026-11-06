#pragma once
#include "controller.hpp"

namespace rl {

    class PlayerController : public Controller {
    public:
        PlayerController();
        virtual ~PlayerController();

        virtual void update() override;
    };

}
