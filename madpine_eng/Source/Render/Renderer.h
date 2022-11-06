//
// Created by Murilo on 31/10/2022.
//
#ifndef SANDBOX_RENDERER_H
#define SANDBOX_RENDERER_H

#include "../Dependencies.h"
#include "../Components.h"

#include<cassert>
#include<fstream>
#include "array"

namespace Renderer {
    struct QuadShape{
        std::array<Components::Vertex, 4> quad;
    };
    struct Quad {
        Quad(flecs::world& ecs);
    };
}

GLuint LoadShader(const char* vert, const char* frag);
GLuint LoadTexture(const char* textureFile);

GLuint NewQuadBase(std::array<Components::Vertex, 4>& quad);
#endif //SANDBOX_RENDERER_H
