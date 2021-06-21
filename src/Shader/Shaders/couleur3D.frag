// Version du GLSL

#version 150 compatibility
#extension GL_ARB_explicit_attrib_location : require
#extension GL_ARB_explicit_uniform_location : require


// Entr�e

in vec3 color;


// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{
    // Couleur finale du pixel

    out_Color = vec4(color, 1.0);
}
