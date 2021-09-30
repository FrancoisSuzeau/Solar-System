// Version du GLSL

#version 330 core


// Entr�e

in vec3 color;
uniform vec3 color2;
uniform bool hdr;


// Sortie 

layout (location = 0) out vec4 FragColor;


// Fonction main

void main()
{
    // Couleur finale du pixel
    vec3 correct_color = vec3(0.2, 0.2, 0.2);
    vec3 result;
    if(hdr)
    {
        result = correct_color * color2;
        
    }
    else
    {
        result = color2;
    }

    FragColor = vec4(result, 1.0);
}
