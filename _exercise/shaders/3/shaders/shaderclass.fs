#version 330 core
out vec4 FragColor;

in vec4 posColor;

void main()
{
    FragColor = posColor;
}