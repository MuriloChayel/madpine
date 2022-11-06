#version 330 core

uniform sampler2D textureSampler;

out vec4 outColor;

in vec3 color;
in vec2 uv;

void main(){
    vec4 texture_color = texture(textureSampler, uv).rgba;

    outColor = texture_color;
}