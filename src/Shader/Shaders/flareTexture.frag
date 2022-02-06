// Version du GLSL

#version 400 core


// Entr�e

in vec2 coordTexture;


// Uniform

uniform sampler2D texture0;


layout (location = 0) out vec4 FragColor;

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
    
    FragColor = vec4(objectColor, 1.0);
    
}
