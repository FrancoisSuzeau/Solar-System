// Version du GLSL

#version 150 core


// Entr�e

in vec2 coordTexture;
uniform vec3 atmoColor;

uniform sampler2D texture;
uniform bool hdr;

// Fonction main

void main()
{
    // *********************************************** calculate png transparency ***************************************************
    vec4 alpha_color = texture2D(texture, coordTexture);
    if(alpha_color.r < 0.1)
    {
        discard;
    }

   // *********************************************** bind texture with color unit to fragment coordinate WITH transparency ***************************************************
    vec3 objectColor = texture(texture, coordTexture).rgb * atmoColor;
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
    
    gl_FragColor = trans;
    
}