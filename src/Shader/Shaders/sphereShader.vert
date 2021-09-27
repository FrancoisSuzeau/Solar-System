#version 330 core

//input vertex data, different for all execution of this shader
attribute vec3 in_Vertex;

//output data : will be interpolated for each element
varying vec2 UV;

uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 light_src;

out vec3 Normal;
out vec3 FragPos;

void main()
{
    gl_Position = projection * modelview * vec4(in_Vertex, 1.0);

    FragPos = vec3(light_src * vec4(in_Vertex, 1.0));
    Normal = mat3(transpose(inverse(light_src))) * in_Vertex;
}