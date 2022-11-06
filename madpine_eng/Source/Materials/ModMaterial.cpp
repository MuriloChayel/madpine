//
// Created by Murilo on 02/11/2022.
//

#include "ModMaterial.h"


namespace Material{

    ApplyShader::ApplyShader(flecs::world& ecs){

        auto sprite = ecs.query<SpriteRenderer::SpriteID>();

        ecs.observer<SpriteRenderer::SpriteID>()
            .event(flecs::OnAdd)
            .each([](SpriteRenderer::SpriteID& sp){
                sp.shader_id = LoadShader("Shaders/vert.glsl", "Shaders/frag.glsl");
            });
    }
}