//
// Created by Murilo on 06/11/2022.
//

#include "Transform.h"

namespace Transform{
    Transform::Transform(flecs::world &ecs) {
        ecs.observer<Components::Transform>()
                .event(flecs::OnAdd)
                .each([](flecs::entity e, Components::Transform){
                    e.set<Components::Position>({0, 1});
                    e.set<Components::Scale>({.32, .32});
                });
    }
}