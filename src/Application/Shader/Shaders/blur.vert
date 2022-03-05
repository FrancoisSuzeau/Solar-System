#version 400 core

in vec3 in_Vertex;
in vec2 in_TexCoord0;

out vec2 TexCoords;

void main()
{
    TexCoords = in_TexCoord0;
    gl_Position = vec4(in_Vertex, 1.0);
    
} 