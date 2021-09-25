// Version du GLSL

#version 330 core


// Entr�e

in vec2 coordTexture;
uniform vec3 atmoColor;

uniform sampler2D texture0;
uniform bool hdr;
layout (location = 0) out vec4 FragColor;

// Fonction main

void main()
{
    // *********************************************** calculate png transparency ***************************************************
    vec4 alpha_color = texture2D(texture0, coordTexture);
    if(alpha_color.r < 0.1)
    {
        discard;
    }

   // *********************************************** bind texture0 with color unit to fragment coordinate WITH transparency ***************************************************
    vec3 objectColor = texture(texture0, coordTexture).rgb * atmoColor;
    float min_Transparency;
    if(hdr)
    {
        min_Transparency = 0.8;
    }
    else
    {
        min_Transparency = 0.69;
    }

    vec4 trans = max(vec4(0.0), ((vec4(objectColor, 1.0)) - min_Transparency));
    
    FragColor = trans;
    
}