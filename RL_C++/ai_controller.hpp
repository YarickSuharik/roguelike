#pragma once
#include "base_controller.hpp"

namespace rl {

    class AIController : public BaseController {
    public:
        AIController();
        virtual ~AIController();

        virtual void makeStep() override;
        virtual std::unique_ptr<BaseController> clone() const override;
    };

}