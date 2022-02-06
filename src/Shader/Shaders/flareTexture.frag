// Version du GLSL

#version 400 core


// Entr�e

in vec2 coordTexture;


// Uniform

uniform sampler2D texture0;
uniform float brightness;


layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;


// Fonction main

void main()
{
    // *********************************************** calculate png transparency ***************************************************
    vec4 alpha_color = texture2D(texture0, coordTexture);
    if(alpha_color.a < 0.1)
    {
        discard;
    }

    vec2 texCoord = coordTexture;
    

    vec3 objectColor = texture(texture0, texCoord).rgb;

    // float brightness2 = dot(objectColor, vec3(0.2126, 0.7152, 0.0722));
    // if(brightness2 > 1.0)
    //     BrightColor = vec4(objectColor, 1.0);
    // else
    //     BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    
    FragColor = vec4(objectColor, 1.0);
    FragColor.a *= brightness * 0.8;
    
}
