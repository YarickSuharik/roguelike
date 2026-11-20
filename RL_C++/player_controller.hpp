#pragma once
#include "base_controller.hpp"

namespace rl {

    class PlayerController : public BaseController {
    public:
        PlayerController();
        virtual ~PlayerController();

        virtual void makeStep() override;
    };

}