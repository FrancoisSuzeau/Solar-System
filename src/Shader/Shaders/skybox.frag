#version 400 core

in vec3 TexCoords;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform samplerCube skybox;

void main()
{
    vec3 objectColor = texture(skybox, TexCoords).rgb;
    
    vec3 result = objectColor;
    FragColor = vec4(result, 1.0);
    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 2.0)
        BrightColor = vec4(result, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}