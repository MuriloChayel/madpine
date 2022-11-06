//
// Created by Murilo on 13/08/2022.
//

#include "Camera.h"

glm::mat4 Create2dCamera(float WIDTH, float HEIGHT){

    //model matrix
    auto model = glm::identity<glm::mat4>();

    //view matrix
    auto eye = glm::vec3 {0.0f, 0.0f, 5.0f};
    auto center = glm::vec3 {0.0f, 0.0f, 0.0f};
    auto up = glm::vec3 {0.0f, 1.0f, 0.0f};
    auto view = glm::lookAt(eye, center, up);

    //projection
    constexpr float fov = glm::radians(45.0f); //angulo abertura
    float aspectRatio = WIDTH / HEIGHT; // porporcao tela
    float near = 0.001f;
    float far = 1000.0f;
    auto projection = glm::perspective(fov, aspectRatio, near, far);

    //model view projection
    auto mvp = projection * view * model;

    return mvp;

}