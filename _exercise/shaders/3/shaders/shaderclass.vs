#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float offset;
out vec4 posColor;

void main()
{
    gl_Position = vec4(aPos.x + offset, aPos.yz, 1.0);
    posColor = gl_Position;
}