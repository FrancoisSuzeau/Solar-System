// Version du GLSL

#version 150 core


// Entr�es

in vec3 in_Vertex;
in vec2 in_TexCoord0;


// Uniform

uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 light_src;

out vec3 Normal;
out vec3 FragPos;


// Sortie

out vec2 coordTexture;


// Fonction main

void main()
{
    // Position finale du vertex en 3D

    gl_Position = projection * modelview * vec4(in_Vertex, 1.0);


    // Envoi des coordonn�es de texture au Fragment Shader

    coordTexture = in_TexCoord0;

    FragPos = vec3(light_src * vec4(in_Vertex, 1.0));
    Normal = mat3(transpose(inverse(light_src))) * in_Vertex;
}