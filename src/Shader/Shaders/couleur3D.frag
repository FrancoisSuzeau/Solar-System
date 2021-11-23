// Version du GLSL

#version 330 core


// Entr�e

in vec3 color;
uniform vec3 color2;
uniform bool hdr;


// Sortie 
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;


// Fonction main

void main()
{
    // Couleur finale du pixel
    vec3 correct_color = vec3(0.15, 0.15, 0.15);
    vec3 result;
    if(hdr)
    {
        result = correct_color * color2;
        
    }
    else
    {
        result = color2;
    }

    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(result, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    
    FragColor = vec4(result, 1.0);
}
