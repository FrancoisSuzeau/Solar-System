#version 330 core

uniform float transparency;


layout (location = 0) out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 1.0, 1.0, transparency);
}