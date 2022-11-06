//
// Created by Murilo on 02/11/2022.
//

#ifndef SANDBOX_MODMATERIAL_H
#define SANDBOX_MODMATERIAL_H
#include "../Dependencies.h"

namespace Material{
    struct ApplyShader{
        explicit ApplyShader(flecs::world& world);
    };
}

#endif //SANDBOX_MODMATERIAL_H
