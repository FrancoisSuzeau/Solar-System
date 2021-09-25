// Version du GLSL

#version 330 core


// Entr�e

in vec2 coordTexture;

// Uniform

uniform sampler2D texture;
layout (location = 0) out vec4 FragColor;


// Fonction main

void main()
{
    // Couleur du pixel
    vec4 alpha_color = texture2D(texture, coordTexture);
    if(alpha_color.r < 0.1)
    {
        discard;
    }
    
    FragColor = texture(texture, coordTexture);
}