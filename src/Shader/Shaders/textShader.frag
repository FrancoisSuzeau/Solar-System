// Version du GLSL

#version 330 core


// Entr�e

in vec2 coordTexture;

// Uniform

uniform sampler2D texture0;
layout (location = 0) out vec4 FragColor;


// Fonction main

void main()
{
    // Couleur du pixel
    vec4 alpha_color = texture2D(texture0, coordTexture);
    if(alpha_color.r < 0.1)
    {
        discard;
    }
    
    FragColor = texture(texture0, coordTexture);
}