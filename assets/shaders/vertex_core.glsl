#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextCoord;
//uniform variable
uniform mat4 transform;

out vec2 textCoord;
out vec3 ourColor;

void main() {
    //gl_Position = transform * vec4(aPos, 1.0);
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    textCoord = aTextCoord;
}