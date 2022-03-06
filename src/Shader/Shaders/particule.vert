#version 400 core

//input vertex data, different for all execution of this shader
in vec3 in_Vertex;

//output data : will be interpolated for each element
// varying vec2 UV;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 FragPos;

void main()
{
    gl_Position = projection * view * (model * vec4(in_Vertex, 1.0));

    FragPos = vec3(model * vec4(in_Vertex, 1.0));
}