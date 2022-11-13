//
// Created by Murilo on 31/10/2022.
//
#include "Renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::string ReadFile(const char* filePath) {
    std::string fileContent;
    if (std::ifstream fileStream{ filePath, std::ios::in }) {
        //ler dentro do fileContent o conteudo do arquivo
        fileContent.assign(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
    }

    //std::cout << fileContent << std::endl;

    return fileContent;
}
GLuint LoadShader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    std::string vertexShaderSource = ReadFile(vertexShaderPath);
    std::string fragmentShaderSource = ReadFile(fragmentShaderPath);

    if(vertexShaderSource.empty()){
        std::cout<<"empty"<<std::endl;
        system("pause");
    }

    if(fragmentShaderSource.empty()){
        std::cout<<"empty"<<std::endl;
        system("pause");
    }

    assert(!vertexShaderSource.empty());
    assert(!fragmentShaderSource.empty());

    const char* vertexShaderSourcePtr = vertexShaderSource.c_str();
    const char* fragmentShaderSourcePtr = fragmentShaderSource.c_str();


    glShaderSource(vertexShader, 1, &vertexShaderSourcePtr, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourcePtr, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
GLuint NewQuadBase(std::array<Components::Vertex, 4>& quad){

    //element buffer object
    const GLuint indices[6] = {
            0, 1, 2,
            0, 3, 2
    };

    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers (1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),  reinterpret_cast<void*>(offsetof(Components::Vertex, uv)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBindVertexArray(0);

    return vao;
}
GLuint LoadTexture(const char* textureFile){

    stbi_set_flip_vertically_on_load(true);

    int width = 0, height = 0, numberOfComponents = 0;

    unsigned char* textureData = stbi_load(textureFile, &width, &height, &numberOfComponents, 4);
    assert(textureData);

    GLuint textureID;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 width,
                 height,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 textureData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,0);

    stbi_image_free(textureData);

    return textureID;
}

//render module
namespace Renderer{
    Quad::Quad(flecs::world& ecs){

    ecs.observer<QuadShape, Components::Position, Components::Scale>()
        .event(flecs::OnAdd)
        .each([](flecs::entity e, QuadShape& qs, Components::Position& p, Components::Scale& s){
            qs.quad = {
                    Components::Vertex{glm::vec3 {(-1.0f * s.x) + p.x, (-1.0f * s.y) + p.y, 0.0f}, glm::vec2 {0, 0}},  // l b
                    Components::Vertex{glm::vec3 {(1.0f * s.x)  + p.x, (-1.0f * s.y) + p.y, 0.0f}, glm::vec2{ 1, 0}},  // r b
                    Components::Vertex{glm::vec3 {(1.0f * s.x)  + p.x, (1.0f * s.y)  + p.y, 0.0f}, glm::vec2{ 1, 1}},  // t r
                    Components::Vertex{glm::vec3 {(-1.0f * s.x) + p.x, (1.0f * s.y) + p.y, 0.0f}, glm::vec2{ 0, 1}},  //  tb
            };
        });
    }
}


