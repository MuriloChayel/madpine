//
// Created by Murilo on 02/11/2022.
//

#include "ModCamera.h"

namespace Camera{
    glm::mat4 mvp(glm::vec3 pos){
        //model matrix
        auto model = glm::identity<glm::mat4>();

        //view matrix
        auto eye = pos;
        auto center = glm::vec3 {0.0f, 0.0f, 0.0f};
        auto up = glm::vec3 {0.0f, 1.0f, 0.0f};
        auto view = glm::lookAt(eye, center, up);

        //projection
        constexpr float fov = glm::radians(45.0f); //angulo abertura
        float aspectRatio = 1280.0f / 720.0f; // porporcao tela
        float near = 0.001f;
        float far = 1000.0f;
        auto projection = glm::perspective(fov, aspectRatio, near, far);

        //model view projection
        auto mvp = projection * view * model;
        return mvp;
    }
    Camera::Camera(flecs::world& ecs) {

        ecs.system<CameraID>()
            .kind(flecs::OnLoad)
            .each([](CameraID& cam){
                cam.mvp = mvp(cam.pos);
            });
    }
}

