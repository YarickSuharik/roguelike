#pragma once
#include "base_controller.hpp"

namespace rl {

    class PlayerController final : public BaseController {
    public:
        PlayerController();
        virtual ~PlayerController();

        virtual void makeStep() override;
        virtual std::unique_ptr<BaseController> clone() const override;
        virtual std::string describe() const override;
    };

}