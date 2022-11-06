//
// Created by Murilo on 02/11/2022.
//

#include "WindowMod.h"
#include "iostream"

namespace Window{
    Window::Window(flecs::world &ecs) {
        assert(glfwInit() != GL_FALSE);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


        ecs.observer<WindowID, Components::Size, Components::Name>()
            .event(flecs::OnSet)
            .each([](flecs::entity e, WindowID& w, Components::Size& size, Components::Name& name){
                w.w = glfwCreateWindow(size.width, size.height, name.title, NULL, NULL);
                assert(w.w);
                glfwMakeContextCurrent(w.w);
                assert(glewInit() == GLEW_OK);
                e.add<Components::Inputable>();
        });

        ecs.system<WindowID>()
            .each([&ecs](flecs::entity e, WindowID& w) {

                if(!glfwWindowShouldClose(w.w)){
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glEnable( GL_BLEND );
                    glClearColor(239.0 / 255.0, 252.0 / 255.0, 224.0 / 255.0, 1.0f );
                    glClear(GL_COLOR_BUFFER_BIT);

                    auto sprite_q = ecs.filter<SpriteRenderer::SpriteID>();
                    auto camera_e = ecs.filter<Camera::CameraID>().first();

                    sprite_q.each([camera_e](SpriteRenderer::SpriteID& sp){
                        glUseProgram(sp.shader_id);
                        glBindVertexArray(sp.sprite_id);
                        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

                        GLint modelViewProjectionLoc = glGetUniformLocation(sp.shader_id, "mvp");
                        glUniformMatrix4fv(modelViewProjectionLoc, 1, GL_FALSE, glm::value_ptr(camera_e.get_ref<Camera::CameraID>()->mvp));

                        glActiveTexture(GL_TEXTURE0);
                        glBindTexture(GL_TEXTURE_2D, sp.texture_id);
                        GLint textureProjectionLoc = glGetUniformLocation(sp.texture_id, "textureSampler");
                        glUniform1i(textureProjectionLoc, 0);

                    });
                    glfwSwapBuffers(w.w);
                    glfwPollEvents();
                }
                else
                {
                    glfwTerminate();
                    ecs.quit();
                }
            });



    }
}
