#version 400 core

in vec3 FragPos;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;


void main()
{
    vec3 result = vec3(5.0);
   
    FragColor = vec4(result, 1.0);

    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 0.0)
        BrightColor = vec4(result, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    
    
}