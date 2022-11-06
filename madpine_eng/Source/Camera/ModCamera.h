//
// Created by Murilo on 02/11/2022.
//

#ifndef SANDBOX_MODCAMERA_H
#define SANDBOX_MODCAMERA_H

#include "../Dependencies.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

namespace Camera{
    struct CameraID{
        glm::mat4 mvp;
        glm::vec3 pos;
    };
    struct Camera{
        Camera(flecs::world& ecs);
    };
}

#endif //SANDBOX_MODCAMERA_H
