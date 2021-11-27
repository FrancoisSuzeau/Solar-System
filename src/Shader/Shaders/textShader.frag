// Version du GLSL

#version 330 core


// Entr�e

in vec2 coordTexture;

// Uniform

uniform sampler2D texture0;
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;


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
    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(FragColor.rgb, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    
}