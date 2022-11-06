//
// Created by Murilo on 05/11/2022.
//

#ifndef SANDBOX_COMPONENTS_H
#define SANDBOX_COMPONENTS_H
#include "Dependencies.h"

namespace Components{


    struct FlagQualquer{};
    struct Inputable{};
    struct Transform{};

    struct Size{
        int width;
        int height;
    };
    struct Name{
        const char* title;
    };
    struct Position{
        float x;
        float y;
    };
    struct Scale{
        float x;
        float y;
    };

    //complex data


    struct Vertex{
        glm::vec3 pos;
        glm::vec2 uv;
    };
}

namespace Physics{
    struct RigidBd2D{};

    struct Velocity{
        float x;
        float y;
    };
    struct Acceleration{
        float x;
        float y;
    };
}
#endif //SANDBOX_COMPONENTS_H
