//
// Created by Murilo on 06/11/2022.
//
#include "RigidBody2D.h"

namespace RigidBody2D{


    RigidBody2D::RigidBody2D(flecs::world &ecs) {

        ecs.observer<Physics::RigidBd2D>()
                .event(flecs::OnAdd)
                .each([](flecs::entity e, Physics::RigidBd2D) {
                    e.add<Physics::Velocity>();
                    e.set<Physics::Acceleration>({0,-0.98});
                });

        ecs.system<SpriteRenderer::SpriteID, Physics::Velocity, Physics::Acceleration, Renderer::QuadShape>()
                .kind(flecs::PostUpdate)
                .each([&](SpriteRenderer::SpriteID& sp, Physics::Velocity& v, Physics::Acceleration& a, Renderer::QuadShape& qs){
//
                    v.x = v.x + a.x * ecs.delta_time();
                    v.y = v.y + a.y * ecs.delta_time();

                    for(auto & q : qs.quad) {
                        q.pos.x += v.x;
                        q.pos.y += v.y * ecs.delta_time();
                    }

                    glBindBuffer(GL_ARRAY_BUFFER, 1);
                    glBufferSubData(GL_ARRAY_BUFFER, 0, 80, &qs.quad[0]);
                    glBindBuffer(GL_ARRAY_BUFFER, 0);
                });
    }
}