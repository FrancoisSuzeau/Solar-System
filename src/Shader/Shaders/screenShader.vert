#version 330 core
in vec3 in_Vertex;
in vec2 in_TexCoord0;

uniform mat4 projection;
uniform mat4 modelview;

out vec2 TexCoords;

void main()
{
    TexCoords = in_TexCoord0;
    gl_Position = projection * modelview * vec4(in_Vertex, 1.0); 
}  