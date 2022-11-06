//
// Created by Murilo on 02/11/2022.
//

#include "ModSpriteRenderer.h"

namespace SpriteRenderer {

    Sprite::Sprite(flecs::world& ecs) {

    ecs.observer<SpriteID, Renderer::QuadShape>()
        .event(flecs::OnAdd)
        .each([](flecs::entity e, SpriteID& sp, Renderer::QuadShape& qs){
            sp.sprite_id = NewQuadBase(qs.quad);
            sp.texture_id = LoadTexture("Sprites/josue.png");
        });
    }
}