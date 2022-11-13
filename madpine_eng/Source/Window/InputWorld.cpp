//
// Created by Murilo on 06/11/2022.
//

#include "InputWorld.h"

void InputWorld::KeyBoard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    std::cout << "teste" << std::endl;
//        ecs.filter_builder<Components::FlagQualquer>()
//            .term(flecs::System)
//            .build()
//            .each([](flecs::entity e, Components::FlagQualquer){
//                flecs::system(ecs, e).run();
//            });

}

InputWorld::InputWorld(flecs::world &ecs){
    this->ecs = ecs.get_world();

    ecs.observer<Window::WindowID, Components::Inputable>()
            .event(flecs::OnAdd)
            .each([this](Window::WindowID& w, Components::Inputable){
                //glfwSetMouseButtonCallback(w.w, Mouse_btns);
                glfwSetKeyCallback(w.w, this->KeyBoard);

            });
    ecs.system< Camera::CameraID>()
            .kind<Components::FlagQualquer>()
            .iter([&](flecs::iter it, Camera::CameraID* cam){
                //cam->pos.x += axis.x * ecs.delta_time() * 10;
                //cam->pos.y += axis.y * it.delta_time() * 10;
            });
    ecs.system<Components::Size>()
            .kind<Components::FlagQualquer>()
            .each([](Components::Size s){
            });
}