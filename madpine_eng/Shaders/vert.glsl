#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 UV;
layout(location = 2) in vec3 Color;

uniform mat4 mvp;

out vec3 color;
out vec2 uv;

void main(){
    uv = UV;
    color = Color;
    gl_Position = mvp * vec4(vertexPosition_modelspace, 1.0);
}