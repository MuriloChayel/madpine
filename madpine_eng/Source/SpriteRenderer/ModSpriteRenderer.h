//
// Created by Murilo on 02/11/2022.
//

#ifndef SANDBOX_MODSPRITERENDERER_H
#define SANDBOX_MODSPRITERENDERER_H

#include "../Dependencies.h"
#include "array"


namespace SpriteRenderer {

    struct SpriteID{
        GLuint sprite_id;// vao
        GLuint texture_id;
        GLuint shader_id;
    };

    struct Sprite{
        explicit Sprite(flecs::world& world);
    };
}

#endif //SANDBOX_MODSPRITERENDERER_H
