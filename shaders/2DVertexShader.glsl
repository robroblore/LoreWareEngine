#version 460 core

layout(location = 0) in vec2 pos;

void main() {
    vec4 finalPos = vec4(pos, 0f, 1f);
    gl_Position = pos;
}