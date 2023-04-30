#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include <memory>
#include "Controller.h"

class InputController {
    public:
    void HandleInput(shared_ptr<Controller> controller, bool &running) const;
};

#endif