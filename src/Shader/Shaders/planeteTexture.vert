#version 150 core

attribute vec3 in_Vertex;
varying vec4 texCoords;
uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;


out vec3 Normal;
out vec3 FragPos;


void main(void) {

    mat4 mp = projection * view * model;

    gl_Position = mp * vec4(in_Vertex, 1.0);
    texCoords = vec4(in_Vertex, 1.0);


    FragPos = vec3(model * vec4(in_Vertex, 1.0));
    Normal = mat3(transpose(inverse(model))) * in_Vertex;
    //Normal = in_Vertex;
}