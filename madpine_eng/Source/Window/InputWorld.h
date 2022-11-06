//
// Created by Murilo on 06/11/2022.
//

#ifndef SANDBOX_INPUTWORLD_H
#define SANDBOX_INPUTWORLD_H

#include "../Dependencies.h"

class InputWorld {
private:
    flecs::world ecs;

public:
    explicit InputWorld(flecs::world& ecs);
    static void KeyBoard(GLFWwindow *window, int key, int scancode, int action, int mods);
};



#endif //SANDBOX_INPUTWORLD_H
