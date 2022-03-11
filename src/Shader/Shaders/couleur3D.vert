// Version du GLSL

#version 400 core


// Entr�es

in vec3 in_Vertex;


// Uniform

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


// Fonction main

void main()
{

    gl_Position = projection * view * (model * vec4(in_Vertex, 1.0));

}
