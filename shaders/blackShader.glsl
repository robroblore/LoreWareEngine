#version 460 core

out vec3 color;

uniform vec3 ucolor = vec3(0.,0.,0.);

void main() {
    color = ucolor;
}
