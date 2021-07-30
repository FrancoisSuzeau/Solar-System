// Version du GLSL

#version 150 core


// Entr�e

in vec2 coordTexture;

// Uniform

uniform sampler2D texture;


// Fonction main

void main()
{
    // Couleur du pixel
    vec4 alpha_color = texture2D(texture, coordTexture);
    if(alpha_color.r < 0.1)
    {
        discard;
    }
    
    gl_FragColor = texture(texture, coordTexture);
}