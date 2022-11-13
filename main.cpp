#include "Source/Window/WindowMod.h"


int main() {
    flecs::world ecs;
    ecs.import<Window::Window>();
    ecs.import<InputWorld>();
    ecs.import<Transform::Transform>();

    ecs.import<Renderer::Quad>();
    ecs.import<SpriteRenderer::Sprite>();

    ecs.import<RigidBody2D::RigidBody2D>();

    ecs.import<Material::ApplyShader>();
    ecs.import<Camera::Camera>();

    ecs.entity<>("window")
        .set<Window::WindowID>({nullptr, 10})
        .set<Components::Size>({1280, 720})
        .set<Components::Name>({"Game Window"});

    ecs.entity("Player")
        .add<Components::Transform>() // ok
        .add<Renderer::QuadShape>()
        .add<SpriteRenderer::SpriteID>()
        .add<Physics::RigidBd2D>();

    ecs.entity("MainCamera")
            .set<Camera::CameraID>({glm::mat4{}, glm::vec3 {.01f,0,6}});

    while (ecs.progress());

}

