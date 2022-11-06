//
// Created by Murilo on 02/11/2022.
//

#ifndef SANDBOX_WINDOWMOD_H
#define SANDBOX_WINDOWMOD_H

#include "../Dependencies.h"


namespace Window{
    struct WindowID{
        GLFWwindow* w;
        int p;
    };

    struct Window{
        Window(flecs::world& ecs);
    };
}

#endif //SANDBOX_WINDOWMOD_H
