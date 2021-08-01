// Version du GLSL

#version 150 core


// Entr�e

in vec3 color;
uniform bool hdr;


// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{
    // Couleur finale du pixel
    vec3 correct_color = {0.2, 0.2, 0.2};
    vec3 result;
    if(hdr)
    {
        result = correct_color * color;
    }
    else
    {
        result = color;
    }

    out_Color = vec4(result, 1.0);
}
